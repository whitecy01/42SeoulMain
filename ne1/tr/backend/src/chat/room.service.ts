import { RoomRepository } from "./room.repository";
import { UserRepository } from "../user/user.repository";
import { CreateRoomDto } from "../dto/chat/create-room.dto";
import { RoomStatus } from "./room-status.enum";
import { RoomListRepository } from "./room-list.repository";
import { UserService } from "../user/user.service";
import { HttpException, Injectable } from "@nestjs/common";
import { GetUserDto } from "../dto/chat/get-user.dto";
import { validate } from "class-validator";
import * as bcrypt from "bcryptjs";
import { BanListRepository } from "./ban.repository";
import { FriendRepository } from "../friend/friend.repository";
import { FriendService } from "../friend/friend.service";

@Injectable()
export class RoomService {
    constructor(
        private roomRepository: RoomRepository,
        private userRepository: UserRepository,
        private roomListRepository: RoomListRepository,
        private userService: UserService,
    ) {}

    async createRoom(createRoomDto: CreateRoomDto, res) {
        try {
            let password = createRoomDto.password;
            const roomStatus = createRoomDto.password === "" ? RoomStatus.PUBLIC : RoomStatus.PRIVATE;
            const user = await this.userRepository.findUserById(createRoomDto.userId);
            if (password !== "") {
                const salt = await bcrypt.genSalt();
                password = await bcrypt.hash(createRoomDto.password, salt);
            }
            const room = this.roomRepository.create({
                name: createRoomDto.chennelName,
                password,
                status: roomStatus,
                channelOwner:  user,
                Administrator: [user],
            });
            const errors = await validate(room);
            if (errors.length > 0) {
                throw new Error(`Validation failed: ${errors.join(', ')}`);
            }
            const result = await this.roomRepository.saveRoom(room);
            await this.userRepository.updateJoinedRoom(user.id, result.id);
            this.roomListRepository.initMuteList(createRoomDto.chennelName);
            this.roomListRepository.initBanList(createRoomDto.chennelName);
        } catch (e) {
            res.status(422).json({ message: "422 Unprocessable Entity" })
        }
    }
    
    async enterRoom(userId: number, roomname: string) {
        const user = await this.userRepository.findUserById(userId);
        const room = await this.roomRepository.findRoomByName(roomname);
        if (!room.members.includes(user)) {
            await this.userRepository.updateJoinedRoom(userId, room.id);
        }
        /*
        해쉬된 비밀번호 비교 코드
        if (await bcrypt.compare(password, room.password))
            return success
        */
    }
    
    async ChennelList() {
        return await this.roomRepository.findAll();
    }
    
    async inviteUser(userId, roomId, res) {
        try {
            const room = await this.roomRepository.findRoomById(roomId);
            await this.userRepository.updateJoinedRoom(userId, room.id);
            res.sendStatus(200);
        } catch {
            res.sendStatus(500);
        }
    }
    
    async muteUser(userId: number, roomName: string, res) {
        try {
            const room = await this.roomRepository.findRoomByName(roomName);
            // 그냥 null로 바꿨을 때 postman에서 어떻게 뜨는지,,,?
            await this.userRepository.updateMutedRoom(userId, room.id);
            this.roomListRepository.addMuteList(roomName, userId);
        } catch {
            res.sendStatus(500);
        }
    }
    
    async deleteMute(userId: number) {
        await this.userRepository.updateMutedRoom(userId, null);
    }
    
    async getMembers(roomname: string) {
        const room = await this.roomRepository.findRoomByName(roomname);
        if (room.members)
            return this.userService.usersToDto(room.members);
        return [];
    }
    
    async changePw(roomname: string, pw: string) {
        const status = pw === "" ? RoomStatus.PUBLIC : RoomStatus.PRIVATE;
        if (pw !== "") {
            const salt = await bcrypt.genSalt();
            pw = await bcrypt.hash(pw, salt);
        }
        await this.roomRepository.updateRoom(roomname, pw, status);
    }
    
    async enterRoomPost(userId: number, roomname: string, password: string) {
        const room = await this.roomRepository.findRoomByName(roomname);
        if (this.roomListRepository.isUserInBanList(roomname, userId))
            return false;
        if (room.status === RoomStatus.PRIVATE) {
            const room = await this.roomRepository.findRoomByName(roomname);
            console.log("password: -" + password + "-");
            console.log("room.password: -" + room.password + "-");
            console.log(await bcrypt.compare(password, room.password))
            return await bcrypt.compare(password, room.password);
        }
        return true;
    }
}