import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Game, GameHistory } from './game.entity';
import { HttpException, Injectable } from '@nestjs/common';
import { RoomInfo, SaveSocketDto } from './game.dto';

@Injectable()
export class GameDB {
  constructor(
    @InjectRepository(Game) private gameRepository: Repository<Game>,
    @InjectRepository(GameHistory)
    private gameHistoryRepository: Repository<GameHistory>,
  ) {}

  private async findUserById(userId: number) {
    try {
      const result = await this.gameRepository
        .createQueryBuilder('game')
        .select()
        .where('game.user = :userId', { userId: userId })
        .getOne();
      return result;
    } catch (error) {
      throw new HttpException('DB ID 찾기 실패', 711, {
        cause: new Error('DB 찾기 실패'),
      });
    }
  }

  private async updateGameProfileDB({
    userId,
    calWins,
    calLoses,
    calLadderLevel,
  }) {
    try {
      const result = await this.gameRepository
        .createQueryBuilder()
        .update(Game)
        .set({ wins: calWins, loses: calLoses, ladderLevel: calLadderLevel })
        .where('user = :userId', { userId: userId })
        .execute();
      return result;
    } catch (error) {
      throw new HttpException('세팅에 실패했습니다.', 114, {
        cause: new Error('전적 쓰기 실패'),
      });
    }
  }

  private async insertGameProfileDB({ userId, wins, loses, ladderLevel }) {
    try {
      return this.gameRepository
        .createQueryBuilder()
        .insert()
        .into(Game)
        .values({
          user: userId,
          wins: wins,
          loses: loses,
          ladderLevel: ladderLevel,
        })
        .execute();
    } catch (error) {
      throw new HttpException('게임 전적 update 실패', 752, {
        cause: new Error('DB 삽입 실패'),
      });
    }
  }

  private calculateGameProfile(
    userId: number,
    team: number,
    room: RoomInfo,
    game: Game,
  ) {
    if (team == room.winner) {
      return {
        userId: userId,
        calWins: ++game.wins,
        calLoses: game.loses,
        calLadderLevel: Math.floor(game.wins / 10),
      };
    } else {
      return {
        userId: userId,
        calWins: game.wins,
        calLoses: ++game.loses,
        calLadderLevel: Math.floor(game.wins / 10),
      };
    }
  }

  private makeGameProfile(userId: number, team: number, winner: number) {
    if (team == winner) {
      return {
        userId: userId,
        wins: 1,
        loses: 0,
        ladderLevel: 0,
      };
    }
    return {
      userId: userId,
      wins: 0,
      loses: 1,
      ladderLevel: 0,
    };
  }

  async saveHistory(data: SaveSocketDto, room: RoomInfo) {
    try {
      return await this.gameHistoryRepository
        .createQueryBuilder()
        .insert()
        .into(GameHistory)
        .values({
          user: data.team == 0 ? room.userId : room.opponentId,
          opponent: data.team == 0 ? room.opponentId : room.userId,
          isUserWin: data.team == room.winner ? true : false,
        })
        .execute();
    } catch (error) {
      throw new HttpException('히스토리 업데이트 실패', 751, {
        cause: new Error('DB 삽입 실패'),
      });
    }
  }

  async save(data: SaveSocketDto, room: RoomInfo) {
    console.log('---save----');
    const gameInfo: Game = await this.findUserById(data.userId);
    if (gameInfo != undefined) {
      const updateGameInfo = this.calculateGameProfile(
        data.userId,
        data.team,
        room,
        gameInfo,
      );
      return await this.updateGameProfileDB(updateGameInfo);
    }
    const makeGameInfo = this.makeGameProfile(
      data.userId,
      data.team,
      room.winner,
    );
    return await this.insertGameProfileDB(makeGameInfo);
  }
}
