import { Injectable } from '@nestjs/common';
import { UserRepository } from './user.repository';
import { UserStatus } from './user-status.enum';
import { MainUserDto } from '../dto/main-user.dto';
import { User } from './user.entity';
import { join } from 'path';
import { GetUserDto } from "../dto/chat/get-user.dto";
import { validate } from "class-validator"
import { FriendService } from "../friend/friend.service";
import { ConnectedSockets } from "../socket/connected-sockets.service";
import { GameService } from "../game/game.service";

@Injectable()
export class UserService {
    constructor(private userRepository: UserRepository,
                private connectedSockets: ConnectedSockets,
                private gameService: GameService) {}

    async findMainUserById(id: number): Promise<MainUserDto> {
        const user = await this.userRepository.findUserById(id);
        const sliceIndx = user.avatar.search('upload');
        return {
            id: user.id,
            username: user.username,
            avatar: user.avatar.slice(sliceIndx),
            twofactorauth: user.twofactorauth,
        };
    }
    
    public usersToDto(users: User[]) {
        let result: GetUserDto[] = [];
        for (const user of users) {
            const sliceIndx = user.avatar.search('upload');
            result.push({
                id: user.id,
                status: this.getStatus(user.id),
                username: user.username,
                avatar: user.avatar.slice(sliceIndx),
            });
        }
        return result;
    }
    
    async createUser(intraId: string, accessToken: string): Promise<User> {
        let user = await this.userRepository.findOneBy({ intraId });
        if (!user) {
            user = this.userRepository.create({
                token: accessToken,
                intraId: intraId,
                avatar: '/upload/profile/image/default.png',
            });
        }
        return await this.userRepository.saveUser(user);
    }
    
    async updateUsername(id: number, username: string, res) {
        try {            
            const user = await this.userRepository.findUserById(id);
            user.username = username;
            const errors = await validate(user);
            if (errors.length > 0) {
                throw new Error(`Validation failed: ${errors.join(', ')}`);
            }
            await this.userRepository.updateUsername(id, username);
        } catch {
            res.status(400).json({ message: "Bad Request" });
        }
    }
    
    getStatus(id: number) {
        if (this.connectedSockets.hasUserId(id)) {
            if (this.gameService.isGaming(id))
                return "GAMING";
            return "ONLINE";
        } else {
            return "OFFLINE";
        }
    }
    
    /* test */
    async getAllUser(): Promise<User[]> {
        return await this.userRepository.findAllUser();
    }
    
    async addUser(user: User) {
        const found = await this.userRepository.findBy({ username: user.username });
        // 차후 변경
        if (found.length >= 1) return null;
        return await this.userRepository.saveUser(user);
    }
    
    async initUser() {
        const defaultAvatarPath = join(
            __dirname,
            '../../',
            'upload/profile/image/default.png',
        );
        
        await this.addUser(
            this.userRepository.create({
                token: '1234',
                intraId: 'user1',
                username: 'user1',
                avatar: defaultAvatarPath,
            }),
        );
        await this.addUser(
            this.userRepository.create({
                token: '1234',
                intraId: 'user2',
                username: 'user2',
                avatar: defaultAvatarPath,
            }),
        );
        await this.addUser(
            this.userRepository.create({
                token: '1234',
                intraId: 'user3',
                username: 'user3',
                avatar: defaultAvatarPath,
            }),
        );
    }
}
