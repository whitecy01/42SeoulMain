import { DataSource, Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';
import { Friend } from './friend.entity';
import { HttpException } from "@nestjs/common";

export class FriendRepository extends Repository<Friend> {
    constructor(@InjectRepository(Friend) private dataSource: DataSource) {
        super(Friend, dataSource.manager); // 변경
    }
    
    /* find */
    async findFriendsByUserId(id: number) {
        try {
            return await this
                .createQueryBuilder('friend')
                .where('friend.userId = :id', { id })
                .getMany();
        } catch {
            throw new HttpException('cannot find friends', 404);
        }
    }
    
    async findFriendByUsername(username: string) {
        const result = this.findOneBy({ username });
        if (!result)
            throw new HttpException('cannot find friend', 404);
        return result;
    }
    
    async deleteFriendByUser(id: number, name: string) {
        try {
            await this.createQueryBuilder('Friend')
                .delete()
                .from('public.friend')
                .where('userId = :id', { id })
                .andWhere('username = :name', { name })
                .execute();
        } catch {
            throw new HttpException('cannot delete friend', 422);
        }
    }
    
    async deleteFriendByUserIdIntraId(id: number, name: string) {
        try {
            await this.createQueryBuilder('Friend')
                .delete()
                .from('public.friend')
                .where('userId = :id', { id })
                .andWhere('intraId = :name', { name })
                .execute();
        } catch {
            throw new HttpException('cannot delete friend', 422);
        }
    }
    
    /* save */
    async saveFriend(friend: Friend) {
        try {
            await this.save(friend);
        } catch {
            throw new HttpException('cannot save friend', 422);
        }
    }
}
