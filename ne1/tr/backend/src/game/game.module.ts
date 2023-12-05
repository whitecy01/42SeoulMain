import { Module } from '@nestjs/common';
import { GameGateWay } from './game.gateway';
import { GameLogic } from './game.gameLogic';
import { GameService } from './game.service';
import { GameDB } from './game.db';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Game, GameHistory } from './game.entity';

@Module({
  imports: [TypeOrmModule.forFeature([Game, GameHistory])],
  providers: [GameGateWay, GameService, GameLogic, GameDB],
  exports: [GameGateWay, GameService, GameLogic, GameDB],
})
export class GameModule {}
