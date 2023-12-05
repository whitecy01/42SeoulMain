import { Injectable } from "@nestjs/common";
import { GetUserDto } from "../dto/chat/get-user.dto";
import { RoomListRepository } from "./room-list.repository";
import { UserRepository } from "../user/user.repository";
import { UserService } from "../user/user.service";
import { BanListRepository } from "./ban.repository";
import { RoomRepository } from "./room.repository";
import { ExpelUserDto } from "../dto/socket/expel-user.dto";

@Injectable()
export class BanListService {
    constructor(
        private roomListRepository: RoomListRepository,
        private userRepository: UserRepository,
        private userService: UserService,
        private banListRepository: BanListRepository,
        private roomRepository: RoomRepository
    ) {}
    
    async banUser(data: ExpelUserDto) {
        const user = await this.userRepository.findUserById(data.userid);
        const room = await this.roomRepository.findRoomByName(data.roomname);
        await this.banListRepository.saveBanList(user, room);
    }
    
    async getBanList(roomname: string) {
        let result: GetUserDto[] = [];
        const banList = this.roomListRepository.getBanList(roomname);
        for (const bannedId of banList) {
            const user = await this.userRepository.findUserById(bannedId);
            result.push({
                id: user.id,
                // status: user.status,
                status: this.userService.getStatus(user.id),
                username: user.username,
                avatar: user.avatar.slice(user.avatar.search('upload'))
            });
        }
        return result;
    }
    
    async cancelBanList(roomname: string, userId: number, res) {
        // banList에서 제거
        this.roomListRepository.deleteBanList(roomname, userId);
        // DB에서 제거
        const room = await this.roomRepository.findRoomByName(roomname);
        console.log("userId = " + userId + " | roomId = " + room.id);
        await this.banListRepository.deleteBanList(userId, room.id);
    }
}