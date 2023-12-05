import { BaseEntity, Column, Entity, JoinColumn, OneToMany, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import { User } from "../user/user.entity";
import { RoomStatus } from "./room-status.enum";
import { BanList } from "./ban.entity";
import { IsString, Matches } from 'class-validator';

@Entity()
export class Room extends BaseEntity {

    @PrimaryGeneratedColumn()
    id: number;

    
    @Column({ unique: true })
    @IsString()
    @Matches(/^[a-zA-Z0-9]*$/, {
        message: 'Roomname should only contain alphabets and numbers.',
    })
    name: string;

    @Column()
    password: string;

    @Column()
    status: RoomStatus;

    @OneToOne(type => User, {eager: true})
    @JoinColumn()
    channelOwner: User;
    
    @OneToMany(type => User, Administrator => Administrator.adminRoom, {eager: true})
    Administrator: User[];

    @OneToMany(type => User, members => members.joinedRoom, {eager: true})
    members: User[];
    
    @OneToMany(type => User, mutedList => mutedList.mutedRoom, {eager: true})
    mutedList: User[];

    @OneToMany(type => BanList, bannedUser => bannedUser.bannedRoom, {eager: true})
    bannedList: BanList[];
}