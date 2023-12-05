import { DataSource, Repository } from "typeorm";
import { InjectRepository } from "@nestjs/typeorm";
import { BanList } from "./ban.entity";
import { HttpException } from "@nestjs/common";
import { User } from "../user/user.entity";
import { Room } from "./room.entity";

export class BanListRepository extends Repository<BanList> {
    constructor(@InjectRepository(BanList) private dataSource: DataSource) {
        super(BanList, dataSource.manager)
    }
    
    /* save */
    async saveBanList(bannedUser: User, bannedRoom: Room) {
        try {
            await this.save({
                bannedUser,
                bannedRoom
            })
        } catch {
            throw new HttpException('cannot save banList', 422);
        }
    }
    
    /* delete */
    async deleteBanList(userId: number, roomId: number) {
        try {
            await this.delete({
                bannedUser: { id: userId },
                bannedRoom: { id: roomId },
            });
        } catch {
            throw new HttpException('cannot delete banList', 422);
        }
    }
}
