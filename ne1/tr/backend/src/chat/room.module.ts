import { Module } from "@nestjs/common";
import { RoomController } from "./room.controller";
import { TypeOrmModule } from "@nestjs/typeorm";
import { User } from "../user/user.entity";
import { Room } from "./room.entity";
import { Friend } from "../friend/friend.entity";
import { BanList } from "./ban.entity";
import { UserModule } from "../user/user.module";
import { FriendModule } from "../friend/friend.module";
import { RoomRepository } from "./room.repository";
import { RoomListRepository } from "./room-list.repository";
import { RoomService } from "./room.service";
import { RoomSocketService } from "./room-socket.service";
import { RoomGateway } from "./room.gateway";
import { ConnectedSocketModule } from "../socket/connected-socket.module";
import { BanListService } from "./ban.service";
import { BanListRepository } from "./ban.repository";
import { BanController } from "./ban.controller";

@Module({
  imports: [
    TypeOrmModule.forFeature([Room, User, Friend, BanList]),
    UserModule,
    FriendModule,
      ConnectedSocketModule,
  ],
  controllers: [RoomController, BanController],
  providers: [
      BanListRepository,
    RoomSocketService,
    RoomService,
    RoomListRepository,
      RoomGateway,
    // UserService,
    RoomRepository,
    // UserRepository,
    // FriendService,
    // FriendRepository,
      BanListService,
  ],
  exports: [RoomSocketService,
      RoomGateway,
    RoomService,
    RoomListRepository,
    RoomRepository,
      BanListRepository,
      BanListService
  ]
})
export class RoomModule {}
