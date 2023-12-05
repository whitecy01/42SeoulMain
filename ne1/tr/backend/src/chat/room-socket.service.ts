import { RoomListRepository } from "./room-list.repository";
import { RoomRepository } from "./room.repository";
import { UserRepository } from "../user/user.repository";
import { FriendService } from "../friend/friend.service";
import { UserService } from "../user/user.service";
import { UserStatus } from "../user/user-status.enum";
import { User } from "../user/user.entity";
import { Room } from "./room.entity";
import { ExitRoomDto } from "../dto/chat/exit-room.dto";
import { ConnectFriendDto } from "../dto/chat/connect-friend.dto";
import { RoomService } from "./room.service";
import { Injectable } from "@nestjs/common";
import { ExpelUserDto } from "../dto/socket/expel-user.dto";
import { BanList } from "./ban.entity";
import { BanListRepository } from "./ban.repository";
import { RestoreRoomDto } from "../dto/chat/restore-room.dto";
import { BlockRepository } from "src/friend/block.repository";

@Injectable()
export class RoomSocketService {
    constructor(
        private roomListRepository: RoomListRepository,
        private roomService: RoomService,
        private roomRepository: RoomRepository,
        private userRepository: UserRepository,
        private friendService: FriendService,
        private userService: UserService,
        private banListRepository: BanListRepository,
        private blockRepository: BlockRepository
    ) {}
    
    async connectRoomList(userId: number) {
        if (this.roomListRepository.isUserInRoomList(userId)) {
            return this.roomListRepository.getRoomList(userId);
        } else {
            this.roomListRepository.initRoomList(userId);
            return null;
        }
    }
    
    async restoreRoom(userId: number) {
        let restoreRoomDto: RestoreRoomDto[] = [];
        for (const roomname of this.roomListRepository.getRoomList(userId)) {
            const room = await this.roomRepository.findRoomByName(roomname);
            restoreRoomDto.push({
                type: roomname.indexOf("\|") === -1 ? 'msg' : 'dm',
                roomname: roomname,
                status: room.status,
                admin: room.Administrator.map((admin) => admin.username),
                owner: room.channelOwner.username,
                member: this.userService.usersToDto(room.members)
            })
        }
        return restoreRoomDto;
    }
    
    async enterDmRoom(usernameTo: string, useridFrom: number) {
        const userTo = await this.userRepository.findUserByUsername(usernameTo);
        const userFrom = await this.userRepository.findUserById(useridFrom);
        const dmRoom = this.getDmRoomName(userTo.username, userFrom.username);
        // if (rooms.has(dmRoom)) return null;
        if (!(this.roomListRepository.getRoomList(userFrom.id).includes(dmRoom) &&
            this.roomListRepository.getRoomList(userTo.id).includes(dmRoom))) {
            this.roomListRepository.addRoomList(userTo.id, dmRoom);
            this.roomListRepository.addRoomList(useridFrom, dmRoom);
        }
        return {
            userIdTo: userTo.id,
            usernameFrom: userFrom.username,
            roomName: dmRoom,
            status : "public",
            admin : null,
            owner : null,
            members : this.userService.usersToDto([userFrom, userTo])
        }
    }
    
    async enterMsgRoom(userId: number, roomName: string, rooms) {
        if (rooms.has(roomName)) return null;
        const room = await this.roomRepository.findRoomByName(roomName);
        const user = await this.userRepository.findUserById(userId);
        await this.roomService.enterRoom(userId, roomName);
        this.roomListRepository.addRoomList(userId, roomName);
        return {
            userIdTo: null,
            usernameFrom: user.username,
            roomName,
            status : room.status,
            admin : room.Administrator.map((admin) => admin.username),
            owner : room.channelOwner.username,
            members : this.userService.usersToDto(room.members)
        }
    }
    
    async exitRoom(userId, roomName) : Promise<ExitRoomDto> {
        const user = await this.userRepository.findUserById(userId);
        const room = await this.roomRepository.findRoomByName(roomName);
        
        /* DB 수정 */
        await this.userRepository.updateJoinedRoom(user.id, null);
        await this.userRepository.updateMutedRoom(user.id, null);
        
        /* List 관련 */
        this.roomListRepository.deleteRoomList(userId, roomName);
        this.roomListRepository.deleteMuteList(userId, roomName);
        return await this.checkExitCase(user, room);
    }
    
    async connectFriend(usernameTo: string, userIdFrom: number): Promise<ConnectFriendDto> {
        const friend = await this.userRepository.findUserByUsername(usernameTo);
        const user = await this.userRepository.findUserById(userIdFrom);
        let connectFriendDto: ConnectFriendDto = {
            userIdTo: -1,
            usernameFrom: user.username,
            msg: "success"
        }
        const blockUser = await this.userRepository.findUserByUsername(usernameTo);
        // 없는 친구를 추가하려고 하는 경우
        if (friend === null) {
            connectFriendDto.msg = "존재하지 않는 유저입니다.";
        }
        // 자기자신을 추가하려고 하는 경우
        else if (friend.id === userIdFrom)
            connectFriendDto.msg = "자기자신을 추가할 수 없습니다.";
        // 이미 추가된 친구일 경우
        else if (user.blockList.map((block) => block.intraId).indexOf(blockUser.intraId) !== -1)
            connectFriendDto.msg = "블락된 유저입니다.";
        else if ((friend.friendList.map((friend) => friend.intraId).indexOf(user.intraId) !== -1 ) &&
        // ((user.friendList.map((user) => user.intraId).length === 0) || 
            (user.friendList.map((user) => user.intraId).indexOf(friend.intraId) === -1)) {
            await this.friendService.addFriendAfterDelete(user, friend);
            connectFriendDto.msg = "삭제 후 다시 추가합니다";
        }
        else {
            const friendId = friend.id;
            for (const friends of user.friendList) {
                if (friends.intraId === friend.intraId) {
                    connectFriendDto.msg = "이미 추가한 유저입니다.";
                }
            }
    
            connectFriendDto.userIdTo = friend.id;
            connectFriendDto.usernameFrom = user.username;
        }
        return connectFriendDto;
    }
    
    async expelUser(data: ExpelUserDto) {
        const user = await this.userRepository.findUserById(data.userid);
        const room = await this.roomRepository.findRoomByName(data.roomname);
    
        await this.userRepository.updateJoinedRoom(data.userid, null);
        await this.roomListRepository.deleteRoomList(data.userid, data.roomname);
        await this.roomService.deleteMute(data.userid);
        await this.roomListRepository.deleteMuteList(data.userid, data.roomname);
        
        // 추방당한 사람이 관리자일 경우
        if (room.Administrator.map((admin) => admin.username).indexOf(user.username) !== -1) {
            // 아닌 경우 그사람만 관리자 박탈
            await this.userRepository.updateAdminRoom(user.id, null);
        }
        return user.username;
    }
    
    private async checkExitCase(user: User, room: Room): Promise<ExitRoomDto> {
        let Administrator = room.Administrator;
        let channelOwner = room.channelOwner;
        let exitRoomDto: ExitRoomDto = {
            changeOwner : false,
            username: user.username,
            userId: user.id,
            roomname: room.name,
            admin: room.Administrator.map((admin) => admin.username),
            owner: channelOwner.username
        }
        // 마지막 한명이 나갔을 경우 방 폭파
        if (await this.userRepository.getUsersInRoom(room.id) === 0) {
            await this.userRepository.updateAdminRoom(user.id, null)
            await this.roomRepository.deleteRoomById(room.id);
        }
            // 아닌 경우2 (나간 사람이 channelOwner인 경우)
            //      channelOwner가 아닌 Admin이 있으면 유지
            //      channelOwner가 유일한 Admin일 경우 다른 유저로 위임
        else if (room.channelOwner.username === user.username) {
            let nextMember : User;
            for (let i = 0; i < room.members.length; i++) {
                if (!(room.members[i].username === room.channelOwner.username)) {
                    nextMember = room.members[i];
                    break ;
                }
            }
            if (Administrator.length === 1)
                Administrator = [nextMember];
            channelOwner = nextMember;
            await this.userRepository.updateAdminRoom(room.channelOwner.id, null);
            await this.userRepository.updateAdminRoom(nextMember.id, room.id)
            await this.roomRepository.updateRoomOwner(room.id, channelOwner);
            if (this.roomListRepository.isUserInMuteList(nextMember.id, room.name)) {
                this.roomListRepository.deleteMuteList(nextMember.id, room.name);
                await this.roomService.deleteMute(nextMember.id);
            }
            exitRoomDto.admin = Administrator.map((admin) => admin.username);
            console.log("owner = " + channelOwner.username);
            exitRoomDto.owner = channelOwner.username;
            exitRoomDto.changeOwner = true;
        }
        // 아닌 경우 3 (나간 사람이 Administrator인 경우)
        else if (room.Administrator.map((admin) => admin.username).indexOf(user.username) !== -1 ) {
            await this.userRepository.updateAdminRoom(user.id, null);
            Administrator = Administrator.filter((admin) => admin.username !== user.username);
            // console.log(Administrator);
            exitRoomDto.admin = Administrator.map((admin) => admin.username);
            exitRoomDto.changeOwner = true;
            // console.log("==========exitRoomDto============")
            // console.log(exitRoomDto.admin);
        }
        return exitRoomDto;
    }
    
    private getDmRoomName(usernameTo: string, usernameFrom: string) {
        const list = [usernameTo, usernameFrom].sort();
        return list[0] + " \| " + list[1];
    }
    
    async connectGame(usernameTo: string, userIdFrom: number) {
        const friend = await this.userRepository.findUserByUsername(usernameTo);
        const user = await this.userRepository.findUserById(userIdFrom);
        return {
            userIdTo: friend.id,
            usernameFrom: user.username,
            msg: "game invite"
        }
    }
}