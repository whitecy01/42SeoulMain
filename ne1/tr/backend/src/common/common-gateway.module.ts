import { Module } from '@nestjs/common';
import { CommonGateway } from './common.gateway';
import { RoomModule } from "../chat/room.module";
import { ConnectedSocketModule } from "../socket/connected-socket.module";
import { GameModule } from "../game/game.module";
import { UserModule } from "../user/user.module";

@Module({
  imports: [
      RoomModule,
      ConnectedSocketModule,
      GameModule,
      UserModule
  ],
  controllers: [],
  providers: [ CommonGateway ],
})
export class CommonGatewayModule {}
