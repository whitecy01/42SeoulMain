import { Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';
import { GameLogic } from './game.gameLogic';
import { GameDB } from './game.db';
import { PlaySocketDto, ReadyUser, RoomInfo, SaveSocketDto } from './game.dto';
import { User } from 'src/user/user.entity';

@Injectable()
export class GameService {
  private rooms: Map<number, RoomInfo>;
  private roomIdx: number;
  private userCnt: number;
  private tmpUser: ReadyUser;
  private timeOutMs: number;

  constructor(
    private gameLogic: GameLogic,
    private gameDB: GameDB,
  ) {
    this.roomIdx = 0;
    this.userCnt = 0;
    this.timeOutMs = 5000;
    this.rooms = new Map<number, RoomInfo>();
  }

  applyGame(socket: Socket, user: ReadyUser): number {
    if (this.userCnt === 0) {
      this.tmpUser = user;
      ++this.userCnt;
      socket.join(String(this.roomIdx));
      return this.userCnt;
    } else {
      socket.join(String(this.roomIdx));
    }
    return ++this.userCnt;
  }

  cancelGame(socket: Socket) {
    socket.leave(String(this.roomIdx));
    if (this.userCnt) this.userCnt--;
  }

  deleteRoom(roomNum: number) {
    this.rooms.delete(roomNum);
  }

  createRoom(socket: Socket, user: ReadyUser) {
    this.userCnt = 0;
    const nowTime = Date.now();
    const newRoom = {
      roomNum: this.roomIdx,
      userId: this.tmpUser.userId,
      userBarX: 0,
      userBarY: 0,
      opponentId: user.userId,
      opponentBarX: 0,
      opponentBarY: 0,
      ballX: 300,
      ballY: 200,
      width: 600,
      height: 400,
      startTime: nowTime + 2000,
      userUpdateTime: nowTime,
      opponentUpdateTime: nowTime,
      end: false,
      winner: 0,
      saveCnt: 0,
    };
    this.rooms.set(this.roomIdx, newRoom);
    this.roomIdx++;
    this.userCnt = 0;
    this.gameLogic.ReadyGame(newRoom.roomNum, newRoom.startTime);
    return newRoom;
  }

  checkTimeout({ roomNum, team }) {
    const room = this.rooms.get(roomNum);
    const nowTime = Date.now();

    if (nowTime - room.userUpdateTime > this.timeOutMs) return true;
    if (nowTime - room.opponentUpdateTime > this.timeOutMs) return true;
    if (team === 0) room.userUpdateTime = nowTime;
    else room.opponentUpdateTime = nowTime;
    return false;
  }

  playGame(data: PlaySocketDto) {
    return this.gameLogic.playGame(data);
  }

  async saveGame(data: SaveSocketDto) {
    const room = this.rooms.get(data.roomNum);
    room.winner = data.winner;
    await this.gameDB.save(data, room);
    await this.gameDB.saveHistory(data, room);
    if (room.saveCnt < 1) {
      room.saveCnt++;
      this.rooms.set(data.roomNum, room);
      return;
    }
    this.rooms.delete(data.roomNum);
  }

  getRoomNumFromUserId(data: ReadyUser) {
    let foundRoom: RoomInfo;
    this.rooms.forEach((room) => {
      if (room.userId == data.userId || room.opponentId == data.userId)
        foundRoom = room;
    });
    return foundRoom;
  }

  isGaming(userId: any) {
    const data: ReadyUser = {
      userId: userId,
    };
    if (this.getRoomNumFromUserId(data)) return true;
    return false;
  }
}
