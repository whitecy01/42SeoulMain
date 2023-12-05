import { MiddlewareConsumer, Module, NestModule } from "@nestjs/common";
import { typeORMConfig } from './config/typeorm.config';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from './user/user.module';
import { CommonGatewayModule } from './common/common-gateway.module';
import { FriendModule } from './friend/friend.module';
import { ServeStaticModule } from '@nestjs/serve-static';
import { join } from 'path';
import { AuthModule } from './auth/auth.module';
import { ConfigModule } from '@nestjs/config';
import { GameModule } from './game/game.module';
import { RoomModule } from "./chat/room.module";
import { ConnectedSocketModule } from "./socket/connected-socket.module";
import { TokenMiddleware } from "./middleware/token.middleware";
import { UserController } from "./user/user.controller";
import { ProfileController } from "./profile/profile.controller";
import { FriendController } from "./friend/friend.controller";
import { RoomController } from "./chat/room.controller";
import { BanController } from "./chat/ban.controller";
import { BlockController } from "./friend/block.controller";

@Module({
  imports: [
    TypeOrmModule.forRoot(typeORMConfig),
    CommonGatewayModule,
    UserModule,
    FriendModule,
    AuthModule,
    GameModule,
    RoomModule,
      // MiddlewareModule,
      ConnectedSocketModule,
    ConfigModule.forRoot({
      cache: true,
      isGlobal: true,
    }),
    ServeStaticModule.forRoot({
      rootPath: join(__dirname, '..', 'upload'),
      serveRoot: '/upload',
      exclude: ['/index.html'],
    }),
  ],
  controllers: [],
  providers: [],
})
export class AppModule implements NestModule {
  configure(consumer: MiddlewareConsumer) {
    consumer.apply(TokenMiddleware).forRoutes(UserController, ProfileController, FriendController, RoomController, BanController, BlockController)
  }
}
