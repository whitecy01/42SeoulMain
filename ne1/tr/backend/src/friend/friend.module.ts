import { Module } from '@nestjs/common';
import { FriendService } from './friend.service';
import { FriendController } from './friend.controller';
import { TypeOrmModule } from "@nestjs/typeorm";
import { Friend } from "./friend.entity";
import { FriendRepository } from "./friend.repository";
import { User } from "../user/user.entity";
import { UserModule } from "../user/user.module";
import { Block } from "./block.entity";
import { BlockService } from "./block.service";
import { BlockRepository } from "./block.repository";
import { BlockController } from "./block.controller";

@Module({
  imports: [
    TypeOrmModule.forFeature([Friend, User, Block]),
      UserModule
  ],
  controllers: [FriendController, BlockController],
  providers: [FriendService, FriendRepository, BlockService, BlockRepository],
  exports: [FriendService, FriendRepository, BlockService, BlockRepository]
})
export class FriendModule {}
