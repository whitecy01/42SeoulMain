import { DataSource, Repository } from "typeorm";
import { InjectRepository } from "@nestjs/typeorm";
import { Room } from "./room.entity";
import { HttpException } from "@nestjs/common";
import { User } from "../user/user.entity";
import { RoomStatus } from "./room-status.enum";

export class RoomRepository extends Repository<Room> {
    constructor(@InjectRepository(Room) private dataSource: DataSource) {
        super(Room, dataSource.manager)
    }
    
    /* find method */
    async findRoomById(id: number) {
        const room = await this.findOneBy({ id });
        if (!room)
            throw new HttpException('cannot find room', 404);
        return room;
    }
    
    async findRoomByName(name: string) {
        const room = await this.findOneBy({ name });
        if (!room)
            throw new HttpException('cannot find room', 404);
        return room;
    }
    
    async findAll() {
        try {
            return await this.find();
        } catch {
            throw new HttpException('cannot find room', 404);
        }
    }
    
    /* delete */
    async deleteRoomById(id: number){
        try {
            await this.delete({ id });
        } catch {
            throw new HttpException('cannot delete room', 422);
        }
    }
    
    /* save */
    async saveRoom(room: Room) {
        try {
            return await this.save(room);
        } catch {
            throw new HttpException('cannot save room', 422);
        }
    }
    
    /* update */
    async updateRoomOwner(id: number, channelOwner: User) {
        try {
            await this.update({ id }, { channelOwner });
        } catch {
            throw new HttpException('cannot update room', 422);
        }
    }
    
    async updateRoom(name: string, password: string, status: RoomStatus) {
        try {
            await this.update({ name }, {
                password,
                status,
            });
        } catch {
            throw new HttpException('cannot update room', 422);
        }
    }
}
