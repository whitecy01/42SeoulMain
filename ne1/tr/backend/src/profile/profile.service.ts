import { HttpException, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { randomUUID } from 'crypto';
import { writeFileSync } from 'fs';
import { extname, join } from 'path';
import { Repository } from 'typeorm';
import { User } from 'src/user/user.entity';
import { ProfileDto, ProfileReturnDto } from './profile.dto';
import { Game, GameHistory } from 'src/game/game.entity';
import { UserRepository } from 'src/user/user.repository';

@Injectable()
export class ProfileService {
  constructor(
    private userRepository: UserRepository,
    @InjectRepository(GameHistory)
    private gameHistoryRepository: Repository<GameHistory>,
    @InjectRepository(Game)
    private gameRepository: Repository<Game>,
  ) {}

  private async updateAvatarPathDB(userId: string, imagePath: string) {
    try {
      return await this.userRepository
        .createQueryBuilder()
        .update(User)
        .set({ avatar: imagePath })
        .where('id = :id', { id: userId })
        .execute();
    } catch (e) {
      throw new HttpException('데이터 저장 실패', 606, {
        cause: new Error(`DB 업데이트 실패: ${e}`),
      });
    }
  }

  private async findImagePath(id: number): Promise<string> {
    try {
      const found = await this.userRepository
        .createQueryBuilder('user')
        .select('avatar')
        .where('id = :id', { id })
        .getRawOne();
      return found.avatar;
    } catch (e) {
      throw new HttpException('유효한 이름이 아닙니다.', 608, {
        cause: new Error(`DB search 실패: ${e}`),
      });
    }
  }

  private async foundProfileName(userName: string): Promise<string> {
    try {
      const found = await this.userRepository
        .createQueryBuilder('user')
        .select()
        .where('user.username = :userName', { userName: userName })
        .getRawOne();
      return found.username;
    } catch (error) {
      throw new HttpException('유효한 ID가 아닙니다.', 601, {
        cause: new Error('DB에 존재하지 않는 ID'),
      });
    }
  }

  private async updateDB({ userId, imagePath }): Promise<void> {
    await this.updateAvatarPathDB(userId, imagePath);
  }

  private saveFileToDiskSync({ imagePath, file }): void {
    try {
      writeFileSync(imagePath, file.buffer);
    } catch (error) {
      throw new HttpException('세팅에 실패했습니다.', 604, {
        cause: new Error(`파일 쓰기 실패 : ${error.code}`),
      });
    }
  }

  private async fileSave(
    userId: number,
    file: Express.Multer.File,
  ): Promise<string> {
    const imagePath = join(
      __dirname,
      '../../upload/profile/image',
      randomUUID() + extname(file.originalname),
    );
    this.saveFileToDiskSync({ imagePath, file });
    await this.updateDB({ userId: userId, imagePath });
    return imagePath;
  }

  private async updateUserName({ userName, newName }) {
    try {
      const result = await this.userRepository
        .createQueryBuilder()
        .update(User)
        .set({ username: newName })
        .where('username = :userName', { userName: userName })
        .execute();
      return result;
    } catch (e) {
      if (e.detail.includes('already exists')) {
        throw new HttpException('이미 존재하는 이름입니다.', 611, {
          cause: new Error('DB 이름 쓰기 실패'),
        });
      }
      throw new HttpException('세팅에 실패했습니다.', 114, {
        cause: new Error(`이름 쓰기 실패`),
      });
    }
  }

  // async updateProfile(
  //   profileDto: ProfileDto,
  //   file: Express.Multer.File,
  // ): Promise<ProfileReturnDto> {
  async updateProfile(id: number, file: Express.Multer.File) {
    // if (!file && !profileDto.newName)
    //   throw new HttpException('세팅 정보를 입력해 주세요.', 601, {
    //     cause: new Error('유저 이름 & 빈 파일'),
    //   });
    // const findName = profileDto.newName
    //   ? profileDto.newName
    //   : profileDto.userName;
    // if (profileDto.newName) {
    //   const isUpdated = await this.updateUserName(profileDto);
    //   if (isUpdated.affected === 0) {
    //     throw new HttpException('유효한 네임이 아닙니다.', 608, {
    //       cause: new Error('유저 이름 없음'),
    //     });
    //   }
    // }

    let imagePath = await this.findImagePath(id);
    if (file) imagePath = await this.fileSave(id, file);
    const sliceIndx = imagePath.search('upload');
    return {
      userId: id,
      imagePath: imagePath.slice(sliceIndx),
    };
  }

  async getGameHistory(userId: User) {
    try {

      const result = await this.gameHistoryRepository
        .createQueryBuilder('history')
        .innerJoinAndSelect('history.opponent', 'opponent')
        .select(['opponent.username', 'history.isUserWin'])
        .where('history.user = :userId', { userId: userId })
        .getRawMany();
      return result;
    } catch (error) {
      throw new HttpException('유효한 ID 찾기 실패했습니다.', 114, {
        cause: new Error('ID 찾기 실패'),
      });
    }
  }

  async getGameProfile(username: string) {
    try {
      const user = await this.userRepository.findUserByUsername(username);
      const result = await this.gameRepository
        .createQueryBuilder('game')
        .select(['game.wins', 'game.loses', 'game.ladderLevel'])
        .where('game.user = :userId', { userId: user.id })
        .getOne();
      if (result) return result;
      return {
        wins: 0,
        loses: 0,
        ladderLevel: 0,
      };
    } catch (error) {
      throw new HttpException('유효한 ID 찾기 실패했습니다.', 114, {
        cause: new Error('ID 찾기 실패'),
      });
    }
  }
}
