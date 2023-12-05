import { DataSource, Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';
import { Friend } from './friend.entity';
import { HttpException } from "@nestjs/common";
import { Block } from "./block.entity";

export class BlockRepository extends Repository<Block> {
    constructor(@InjectRepository(Block) private dataSource: DataSource) {
        super(Block, dataSource.manager); // 변경
    }
    
    /* find */
    async findBlocksByUserId(id: number) {
        try {
            return await this
                .createQueryBuilder('block')
                .where('block.userId = :id', { id })
                .getMany();
        } catch {
            throw new HttpException('cannot find block', 404);
        }
    }
    
    async deleteBlockByUser(id: number, name: string) {
        try {
            await this.createQueryBuilder('Block')
                .delete()
                .from('public.block')
                .where('userId = :id', { id })
                .andWhere('username = :name', { name })
                .execute();
        } catch {
            throw new HttpException('cannot delete block', 422);
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
    async saveBlock(block: Block) {
        try {
            await this.save(block);
        } catch {
            throw new HttpException('cannot save block', 422);
        }
    }
}
