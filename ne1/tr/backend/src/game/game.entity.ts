import { User } from 'src/user/user.entity';
import {
  Column,
  Entity,
  JoinColumn,
  ManyToOne,
  OneToOne,
  PrimaryGeneratedColumn,
} from 'typeorm';

@Entity()
export class Game {
  @PrimaryGeneratedColumn('uuid')
  id: number;

  @JoinColumn()
  @OneToOne(() => User)
  user: User;

  @Column()
  wins: number;

  @Column()
  loses: number;

  @Column()
  ladderLevel: number;
}

@Entity()
export class GameHistory {
  @PrimaryGeneratedColumn('uuid')
  id: number;

  @ManyToOne(() => User)
  user: User;

  @ManyToOne(() => User)
  opponent: User;

  @Column()
  isUserWin: boolean;
}
