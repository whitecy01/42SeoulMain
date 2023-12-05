import { DataSource, Repository } from "typeorm";
import { User } from "./user.entity";
import { InjectRepository } from "@nestjs/typeorm";
import { UserStatus } from "./user-status.enum";
import { DummyDto } from "../dto/dummy.dto";
import { HttpException } from "@nestjs/common";
import { Room } from "../chat/room.entity";

export class UserRepository extends Repository<User> {
    constructor(@InjectRepository(User) private dataSource: DataSource) {
        super(User, dataSource.manager); // 변경
    }
    
    /* find method */
    async findUserById(id: number) {
        const user = await this.findOneBy({ id });
        if (!user)
            throw new HttpException(`cannot find user by id`, 404);
        return user;
    }
    
    async findUserByUsername(username: string) {
        const user = await this.findOneBy({ username });
        if (!user)
            throw new HttpException('cannot find user by username', 404);
        return user;
    }
    
    async findUserByIntraId(intraId: string) {
        const user = await this.findOneBy({ intraId });
        if (!user)
            throw new HttpException('cannot find user by intraid', 404);
        return user;
    }
    
    // async findUserIdByFriendName(friendName: string) {
    //     try {
    //         return await this.createQueryBuilder('user')
    //             .select('id')
    //             .where('username = :friendName', { friendName })
    //             .getRawOne();
    //     } catch {
    //         throw new HttpException('cannot find user', 404);
    //     }
    // }
    
    async findAllUser() {
        try {
            return await this.find();
        } catch {
            throw new HttpException('cannot find users', 404);
        }
    }
    
    /* save */
    async saveUser(user: User) {
        try {
            return await this.save(user);
        } catch {
            throw new HttpException('cannot save user', 422);
        }
    }
    
    /* update */
    async updateJoinedRoom(userId: number, roomId: number) {
        try {
            await this.update({ id: userId }, {
                    joinedRoom: { id: roomId },
                },
            );
        } catch {
            throw new HttpException('cannot update user', 422);
        }
    }
    
    async updateMutedRoom(userId: number, roomId: number) {
        try {
            await this.update({ id: userId }, {
                    mutedRoom: { id: roomId },
                },
            );
        } catch {
            throw new HttpException('cannot update user', 422);
        }
    }
    
    async updateAdminRoom(userId: number, roomId: number) {
        try {
            await this.update({ id: userId }, {
                    adminRoom: { id: roomId },
                },
            );
        } catch {
            throw new HttpException('cannot update user', 422);
        }
    }
    
    async updateUsername(id: number, username: string) {
        try {
            await this.update({ id }, { username });
        } catch {
            throw new HttpException('cannot update user', 422);
        }
    }
    
    async getUsersInRoom(roomId) {
        try {
            return await this.createQueryBuilder("user")
                .where("user.joinedRoomId = :id", { id: roomId })
                .getCount();
        } catch {
            throw new HttpException('cannot find users in room', 404);
        }
    }
}
