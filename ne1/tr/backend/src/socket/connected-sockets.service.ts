import { SocketClientDto } from "../dto/socket/socket-client.dto";
import { Injectable } from "@nestjs/common";
import { Socket } from "socket.io";
import { NotificationDto } from "../dto/socket/notification.dto";

@Injectable()
export class ConnectedSockets {
    // userid, SocketClientDto
    private socketList: Map<number, SocketClientDto> = new Map();
    private notification: Map<number, NotificationDto> = new Map();
 
    /* socket list */
    setSocketList(userId: number, socket: Socket) {
        this.socketList.set(userId, {
            clientId: socket.id,
            socket: socket,
        });
    }
    
    deleteSocketList(userId: number) {
        this.socketList.delete(userId);
    }
    
    getSocket(userId: number): Socket {
        if (!this.hasUserId(userId))
            return null;
        return this.socketList.get(userId).socket;
    }
    
    hasUserId(userId: number): boolean {
        return this.socketList.has(userId);
    }
    
    /* notification */
    setNotification(id: number, data: NotificationDto) {
        this.notification.set(id, data);
    }
    
    isUserInNotification(id: number) {
        return this.notification.has(id);
    }
    
    deleteNotification(id: number) {
        this.notification.delete(id);
    }
    
    getNotification(id: number) {
        if (!this.isUserInNotification(id))
            return null;
        return this.notification.get(id);
    }
}