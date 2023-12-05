import { BaseEntity, Column, Entity, ManyToOne, OneToMany, PrimaryGeneratedColumn } from "typeorm";
import { User } from "../user/user.entity";
import { Room } from "./room.entity";

@Entity()
export class BanList extends BaseEntity {
    @PrimaryGeneratedColumn()
    id: number;
    
    @ManyToOne(type => User, bannedUser => bannedUser.bannedList, {eager: false})
    bannedUser: User;
    
    @ManyToOne(type => Room, bannedRoom => bannedRoom.bannedList, {eager: false})
    bannedRoom: Room;
}
