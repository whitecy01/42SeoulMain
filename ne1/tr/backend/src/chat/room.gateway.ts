import {
    SubscribeMessage,
    WebSocketGateway,
    WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { SendMsgDto } from '../dto/socket/send-msg.dto';
import { RoomListRepository } from "./room-list.repository";
import { RoomRepository } from "./room.repository";
import { UserChatDto } from '../dto/socket/user-chat.dto';
import { UserRepository } from '../user/user.repository';
import { DelegateAdminDto } from '../dto/socket/delegate-admin.dto';
import { ConnectSocketDto } from '../dto/socket/connect-socket.dto';
import { FriendService } from '../friend/friend.service';
import { RoomSocketService } from "./room-socket.service";
import { EnterRoomDto } from '../dto/chat/enter-room.dto';
import { ExitRoomDto } from '../dto/chat/exit-room.dto';
import { AddFriendDto } from '../dto/socket/add-friend.dto';
import { ExpelUserDto } from '../dto/socket/expel-user.dto';
import { ConnectedSockets } from "../socket/connected-sockets.service";
import { BanListService } from "./ban.service";
import { BlockRepository } from "../friend/block.repository";

@WebSocketGateway(4242, {
    cors: {
        origin: '*',
        methods: ['GET', 'POST'],
        credentials: true,
    },
})
export class RoomGateway {
    
    constructor(
        private roomSocketService: RoomSocketService,
        private roomListService: RoomListRepository,
        private roomRepository: RoomRepository,
        private userRepository: UserRepository,
        private friendService: FriendService,
        private connectedSockets: ConnectedSockets,
        private banListService: BanListService,
        private blockRepository: BlockRepository
    ) {}
    
    @WebSocketServer()
    server: Server;
    
    async handleRoomConnect(client: Socket, userId: number) {
        if (this.connectedSockets.isUserInNotification(userId)) {
            client.emit('notification',
                this.connectedSockets.getNotification(userId));
            this.connectedSockets.deleteNotification(userId);
        }
        const roomList = await this.roomSocketService.connectRoomList(userId);
        if (roomList !== null) client.join(roomList);
    }
    
    async handleRoomDisconnect(client: Socket, userId: number) {
        const roomList = this.roomListService.getRoomList(userId);
        for (const room of roomList) {
            client.leave(room);
        }
    }
    
    /* chat */
    @SubscribeMessage('restoreChannel')
    async restoreRoom(client: Socket, userId: number) {
        return await this.roomSocketService.restoreRoom(userId);
    }
    
    @SubscribeMessage('enterroom')
    async enterRoom(client: Socket, data: UserChatDto) {
        let enterRoomDto: EnterRoomDto;
        if (data.type === 'dm') {
            enterRoomDto = await this.roomSocketService.enterDmRoom(
                data.roomname,
                data.userid,
            );
            
            if (enterRoomDto === null) return;
            const clientTo: Socket = this.connectedSockets.getSocket(
                enterRoomDto.userIdTo,
            );
            clientTo.join(enterRoomDto.roomName);
        } else if (data.type === 'msg') {
            // 밴 리스트에 유저가 있을 경우 null 반환 => 이거 프론트랑 맞춰야 할 것 같아요
            if (this.roomListService.isUserInBanList(data.roomname, data.userid))
                return ;
            enterRoomDto = await this.roomSocketService.enterMsgRoom(
                data.userid,
                data.roomname,
                client.rooms,
            );
            if (enterRoomDto === null) return;
            client.to(data.roomname).emit('getmessage', {
                type: 'not',
                roomname: data.roomname,
                userid: data.userid,
                username: enterRoomDto.usernameFrom,
                avatar: '',
                msg: `${enterRoomDto.usernameFrom}님이 ${data.roomname}에 입장하셨습니다.`,
            });
        }
        if (!client.rooms.has(enterRoomDto.roomName)) client.join(enterRoomDto.roomName);
        return {
            type: data.type,
            roomname: enterRoomDto.roomName,
            status: enterRoomDto.status,
            admin: enterRoomDto.admin,
            owner: enterRoomDto.owner,
            members: enterRoomDto.members,
        };
    }
    
    @SubscribeMessage('exitroom')
    async exitRoom(client: Socket, data: UserChatDto) {
        if (data.type === 'msg') {
            const exitRoomDto: ExitRoomDto = await this.roomSocketService.exitRoom(
                data.userid,
                data.roomname,
            );
            client.to(data.roomname).emit('getmessage', {
                type: 'not',
                roomname: exitRoomDto.roomname,
                userid: exitRoomDto.userId,
                username: exitRoomDto.username,
                avatar: '',
                msg: `${exitRoomDto.username}님이 ${exitRoomDto.roomname}에서 나가셨습니다.`,
            });
            // if (exitRoomDto.changeAdmin) {
            //     client.to(exitRoomDto.roomname).emit('changeadmin', {
            //         roomname: exitRoomDto.roomname,
            //         admin: exitRoomDto.admin,
            //         owner: exitRoomDto.owner,
            //     });
            // } else
            console.log(exitRoomDto);
            if (exitRoomDto.changeOwner) {
                this.server.to(exitRoomDto.roomname).emit('changeadmin', {
                    roomname: exitRoomDto.roomname,
                    admin: exitRoomDto.admin,
                    owner: exitRoomDto.owner,
                });
            }
        }
        client.leave(data.roomname);
    }
    
    @SubscribeMessage('sendmessage')
    async sendMessage(client: Socket, data: SendMsgDto) {
        const user = await this.userRepository.findUserById(data.userid);
        if (
            data.type === 'msg' &&
            this.roomListService.isUserInMuteList(data.userid, data.roomname)
        ) {
            return {
                mute: true,
            };
        } else {
            const blocks = await this.blockRepository.findBlocksByUserId(data.userid);
            client.to(data.roomname).emit('getmessage', {
                type: data.type,
                roomname: data.roomname,
                userid: data.userid,
                blockList: blocks.map((block) => block.id),
                username: user.username,
                avatar: user.avatar.slice(user.avatar.search('upload')),
                msg: data.msg,
            });
            return {
                mute: false,
            };
        }
    }
    
    @SubscribeMessage('delegateadmin')
    async delegateAdmin(client: Socket, data: DelegateAdminDto) {
        const room = await this.roomRepository.findRoomByName(data.roomname);
        const owner = room.channelOwner.username;
        await this.userRepository.updateAdminRoom(data.userid, room.id);
        const newRoom = await this.roomRepository.findRoomById(room.id);
        this.server.to(data.roomname).emit('changeadmin', {
            roomname: data.roomname,
            admin: newRoom.Administrator.map((admin) => admin.username),
            owner,
        });
    }
    
    // 일단은 data 안의 user가 방에 있다고 가정
    @SubscribeMessage('expeluser')
    async expelUser(client: Socket, data: ExpelUserDto) {
        const username = await this.roomSocketService.expelUser(data);
        const expelClient = this.connectedSockets.getSocket(data.userid);
        if (data.type === 'ban') {
            this.roomListService.addBanList(data.roomname, data.userid);
            await this.banListService.banUser(data);
        }
        this.server.to(data.roomname).emit('getmessage', {
            type: 'not',
            expel: true,
            roomname: data.roomname,
            userid: data.userid,
            username: username,
            avatar: '',
            msg: `${username}님이 ${data.roomname}에서 쫓겨났습니다.`,
        });
        expelClient.leave(data.roomname);
    }
    
    @SubscribeMessage('addfriend')
    async addFriend(client: Socket, data: AddFriendDto) {
        // user1, user2 서로 친구로 등록
        await this.friendService.addFriend(data.userfrom, data.userto);
        const clientTo = this.connectedSockets.getSocket(data.userto);
        client.emit('fetchfriend', { result: 200 });
        clientTo.emit('fetchfriend', { result: 200 });
    }
    
    @SubscribeMessage('connectsocket')
    async connectSocket(client: Socket, data: ConnectSocketDto) {
        
        if (data.type === 'friend') {
            const result = await this.roomSocketService.connectFriend(
                data.userto,
                data.userfrom,
            );
            if (result.msg === 'success') {
                const notDto = {
                    type: 'friend',
                    userid: data.userfrom,
                    username: result.usernameFrom
                }
                const clientTo = this.connectedSockets.getSocket(result.userIdTo);
                if (clientTo === null) {
                    this.connectedSockets.setNotification(result.userIdTo, notDto);
                } else {
                    client.to(clientTo.id).emit('notification',  notDto);
                }
            }
            return result.msg;
        } else if (data.type === 'game') {
            const result = await this.roomSocketService.connectGame(
                data.userto,
                data.userfrom,
            );
            const notDto = {
                type: 'game',
                userid: data.userfrom,
                username: result.usernameFrom
            }
            const clientTo = this.connectedSockets.getSocket(result.userIdTo);
            if (clientTo === null) {
                this.connectedSockets.setNotification(result.userIdTo, notDto);
            } else {
                client.to(clientTo.id).emit('notification',  notDto);
            }
            return "";
        }
    }
}
