import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import { Game } from "../game/game.entity";
import { UserStatus } from "../user/user-status.enum";
import { User } from "../user/user.entity";

@Entity()
export class Friend extends BaseEntity {

    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    username: string;
    
    @Column()
    intraId: string;

    @Column()
    avatar: string;
    
    status: string;

    @ManyToOne(type => User, user => user.friendList, {eager: false})
    user: User
}