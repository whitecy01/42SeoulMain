import {
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameService } from './game.service';

@WebSocketGateway(4242, {
  cors: {
    origin: ['http://localhost:8080', 'http://127.0.0.1:8080'],
    methods: ['GET', 'POST'],
    //credentials: true,
  },
})
export class GameGateWay {
  @WebSocketServer() server: Server;
  constructor(private gameService: GameService) {}

  handleGameConnection(socket: Socket) {
    console.log('connected socket id: ', socket.id);
  }

  handleGameDisconnect(socket: Socket) {
    console.log('disconnect socket id: ', socket.id);
    for (const room of socket.rooms) {
      socket.leave(room);
    }
  }

  @SubscribeMessage('readyGame')
  async readyMessage(socket: Socket, data: any) {
    console.log(data);
    const room = this.gameService.getRoomNumFromUserId(data);
    if (room) {
      socket.join(String(room.roomNum));
      socket.emit('setGame', {
        roomNum: room.roomNum,
        team: data.userId == room.userId ? 0 : 1,
      });
      return;
    }
    const userCnt = this.gameService.applyGame(socket, data);
    if (userCnt === 2) {
      const roomInfo = this.gameService.createRoom(socket, data);
      const sockets = await this.server
        .in(String(roomInfo.roomNum))
        .fetchSockets();
      for (let idx = 0; idx < sockets.length; ++idx) {
        sockets[idx].emit('setGame', {
          roomNum: roomInfo.roomNum,
          team: idx,
        });
      }
    }
  }

  @SubscribeMessage('cancelGame')
  cancelMessage(socket: Socket) {
    this.gameService.cancelGame(socket);
  }

  @SubscribeMessage('playGame')
  async playMessage(socket: Socket, data: any) {
    if (this.gameService.checkTimeout(data)) {
      this.server.to(String(data.roomNum)).emit('timeOutGame');
      this.gameService.deleteRoom(data.roomNum);
      return;
    }
    const playInfo = this.gameService.playGame(data);
    if (playInfo.winner !== undefined) {
      this.server.to(String(data.roomNum)).emit('endGame', playInfo);
    } else {
      this.server.to(String(data.roomNum)).emit('updateGame', playInfo);
    }
  }

  @SubscribeMessage('saveGame')
  async saveMessage(socket: Socket, data: any) {
    this.gameService.saveGame(data);
  }
}
