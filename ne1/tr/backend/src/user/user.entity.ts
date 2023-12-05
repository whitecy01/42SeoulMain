import {
  BaseEntity,
  Column,
  Entity,
  ManyToMany,
  ManyToOne,
  OneToMany,
  PrimaryGeneratedColumn,
  Unique,
} from 'typeorm';
import { Game } from '../game/game.entity';
import { UserStatus } from './user-status.enum';
import { Friend } from '../friend/friend.entity';
import { Room } from '../chat/room.entity';
import { BanList } from '../chat/ban.entity';
import { IsString, Matches } from 'class-validator';
import { Block } from "../friend/block.entity";

@Entity()
export class User extends BaseEntity {
  // 테스트용이라 uuid 뺌
  // 실전에선 꼭 넣을것
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  token: string;

  @Column({ nullable: true })
  secretKey: string;

  @Column({ default: false })
  twofactorauth: boolean;

  @Column({ default: false })
  istwofactorauth: boolean;

  @Column()
  intraId: string;

  @Column({ unique: true, nullable: true })
  @IsString()
  @Matches(/^[a-zA-Z0-9]*$/, {
      message: 'Username should only contain alphabets and numbers.',
  })
  username: string;

  @Column()
  avatar: string;

  // @Column()
  // status: string;

  @OneToMany((type) => Friend, (friendList) => friendList.user, { eager: true })
  friendList: Friend[];
  
  @OneToMany((type) => Block, (blockList) => blockList.user, { eager: true })
  blockList: Block[];
  
  @ManyToOne((type) => Room, (joinedRoom) => joinedRoom.members, {
    eager: false,
  })
  joinedRoom: Room;

  @ManyToOne((type) => Room, (mutedRoom) => mutedRoom.mutedList, {
    eager: false,
  })
  mutedRoom: Room;
  
  @ManyToOne((type) => Room, (adminRoom) => adminRoom.Administrator, {
    eager: false,
  })
  adminRoom: Room;

  @OneToMany((type) => BanList, (bannedRoom) => bannedRoom.bannedUser, {
    eager: true,
  })
  bannedList: BanList[];
}
