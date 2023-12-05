import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { ConnectedSockets } from "../socket/connected-sockets.service";
import { RoomGateway } from "../chat/room.gateway";
import { GameGateWay } from "../game/game.gateway";
import { UserRepository } from "../user/user.repository";

@WebSocketGateway(4242, {
  cors: {
    origin: '*',
    methods: ['GET', 'POST'],
    credentials: true,
  },
})
export class CommonGateway implements OnGatewayConnection, OnGatewayDisconnect {

  constructor(
    private connectedSockets: ConnectedSockets,
    private roomGateway: RoomGateway,
    private gameGateWay: GameGateWay,
    private userRepository: UserRepository
  ) {}

  @WebSocketServer()
  server: Server;

  async handleConnection(client: Socket) {
    const userId = parseInt(<string>client.handshake.query.userid);
    const token = <string>client.handshake.query.token;
    if (!(await this.isValidToken(token, userId))) {
      client.disconnect(true);
      return ;
    }
    this.connectedSockets.setSocketList(userId, client);
    await this.roomGateway.handleRoomConnect(client, userId);
    this.gameGateWay.handleGameConnection(client);
  }

  async handleDisconnect(client: Socket) {
    const userId = parseInt(<string>client.handshake.query.userid);
    this.connectedSockets.deleteSocketList(userId);
    await this.roomGateway.handleRoomDisconnect(client, userId);
    this.gameGateWay.handleGameDisconnect(client);
  }
  
  async isValidToken(token, userId) {
    const user = await this.userRepository.findOneBy({id: userId});
    if (!user)
      return false;
    return user.token === token;
  }
}
