import { User } from 'src/user/user.entity';

export interface ReadyUser {
  userId: User;
}

export interface PlaySocketDto {
  roomNum: number;
  team: number;
  y: number;
}

export interface SaveSocketDto {
  userId: number;
  roomNum: number;
  team: number;
  winner: number;
}

export interface RoomInfo {
  roomNum: number;
  userId: User;
  userBarX: number;
  userBarY: number;
  opponentId: User;
  opponentBarX: number;
  opponentBarY: number;
  ballX: number;
  ballY: number;
  width: number;
  height: number;
  startTime: number;
  userUpdateTime: number;
  opponentUpdateTime: number;
  end: boolean;
  winner: number;
  saveCnt: number;
}
