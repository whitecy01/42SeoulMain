import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import { Game } from "../game/game.entity";
import { UserStatus } from "../user/user-status.enum";
import { User } from "../user/user.entity";

@Entity()
export class Block extends BaseEntity {
    
    @PrimaryGeneratedColumn()
    id: number;
    
    @Column()
    username: string;
    
    @Column()
    intraId: string;
    
    @ManyToOne(type => User, user => user.blockList, {eager: false})
    user: User
}