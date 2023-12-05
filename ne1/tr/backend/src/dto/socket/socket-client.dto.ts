import { Socket } from "socket.io";

export interface SocketClientDto {
    clientId: string;
    socket: Socket;
}