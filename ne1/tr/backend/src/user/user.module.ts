import { Module } from '@nestjs/common';
import { User } from './user.entity';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserController } from './user.controller';
import { UserService } from './user.service';
import { UserRepository } from './user.repository';
import { InitController } from './init.controller';
import { ProfileController } from 'src/profile/profile.controller';
import { ProfileService } from 'src/profile/profile.service';
import { Game, GameHistory } from 'src/game/game.entity';
import { ConnectedSocketModule } from "../socket/connected-socket.module";
import { GameModule } from "../game/game.module";

@Module({
  imports: [TypeOrmModule.forFeature([User, GameHistory, Game]),
  ConnectedSocketModule, GameModule],
  controllers: [InitController, UserController, ProfileController],
  providers: [UserService, UserRepository, ProfileService],
  exports: [UserService, UserRepository, ProfileService],
})
export class UserModule {}
