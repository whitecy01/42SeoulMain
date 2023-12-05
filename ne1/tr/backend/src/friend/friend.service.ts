import { Injectable } from '@nestjs/common';
import { FriendRepository } from "./friend.repository";
import { UserRepository } from "../user/user.repository";
import { Friend } from "./friend.entity";
import { User } from "../user/user.entity";
import { ConnectedSockets } from "../socket/connected-sockets.service";
import { UserService } from "../user/user.service";
import { GetUserDto } from "../dto/chat/get-user.dto";

@Injectable()
export class FriendService {
    constructor(
        private friendRepository: FriendRepository,
        private userRepository: UserRepository,
        private userService: UserService
    ) {}
    
    async addFriendAfterDelete(user: User, friend: User) {
        await this.friendRepository.saveFriend(
            this.friendRepository.create({
                intraId: friend.intraId,
                username: friend.username,
                avatar: friend.avatar,
                user,
            }),
        );
    }

    async addFriend(from: number, to: number) {
        const user = await this.userRepository.findUserById(from);
        const friend = await this.userRepository.findUserById(to);
        
        await this.friendRepository.saveFriend(
            this.friendRepository.create({
                intraId: user.intraId,
                username: user.username,
                avatar: user.avatar,
                user: friend,
            }),
        );
        await this.friendRepository.saveFriend(
            this.friendRepository.create({
                intraId: friend.intraId,
                username: friend.username,
                avatar: friend.avatar,
                user: user,
            }),
        );
    }
    
    async getAllFriend(id: number) {
        let getUserDto: GetUserDto[] = [];
        const friends = await this.friendRepository.findFriendsByUserId(id);
        // friends.filter(friend => friend.avatar = friend.avatar.slice(friend.avatar.search('upload')));
        for (const friend of friends) {
            const user = await this.userRepository.findUserByIntraId(friend.intraId);
            getUserDto.push({
                id: friend.id,
                username: user.username,
                avatar: user.avatar.slice(user.avatar.search('upload')),
                status: this.userService.getStatus(user.id),
            })
            // const userId = await this.userRepository.findUserIdByFriendName(friend.username);
            // friend.status = this.userService.getStatus(userId.id);
        }
        return getUserDto;
    }
    
    async deleteFriend(userId: number, friendId: number) {
        const friendName = (await this.friendRepository.findOneBy({ id: friendId }))
            .username;
        await this.friendRepository.deleteFriendByUser(userId, friendName);
    }
}
