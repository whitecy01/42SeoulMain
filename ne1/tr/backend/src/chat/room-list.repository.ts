import { Injectable } from "@nestjs/common";
import { UserRepository } from "../user/user.repository";
import { RoomRepository } from "./room.repository";

@Injectable()
export class RoomListRepository {
    // userId, rooms[]
    private roomList = new Map<number, string[]>();
    // roomname, userId[]
    private banList = new Map<string, number[]>();
    // roomname, userId[]
    private muteList = new Map<string, number[]>();
    
    /* RoomList */
    initRoomList(userId: number) {
        this.roomList.set(userId, null);
    }
    
    addRoomList(userId: number, roomname: string) {
        if (this.roomList.get(userId) === null)
            this.roomList.set(userId, [roomname]);
        else
            this.roomList.get(userId).push(roomname);
    }

    deleteRoomList(userId: number, roomname: string) {
        this.roomList.set(userId,
            this.roomList.get(userId).filter(deleteName => roomname !== deleteName));
    }

    getRoomList(userId: number) : string[] {
        const result = this.roomList.get(userId);
        if (!result)
            return [];
        return result;
    }

    isUserInRoomList(userId: number) : boolean {
        return this.roomList.has(userId);
    }
    
    /* BanList */
    initBanList(roomName: string) {
        this.banList.set(roomName, null);
    }
    
    addBanList(roomname: string, userId: number) {
        if (this.banList.get(roomname) === null)
            this.banList.set(roomname, [userId]);
        else
            this.banList.get(roomname).push(userId);
    }
    
    getBanList(roomname: string) : number[] {
        const result = this.banList.get(roomname);
        if (!result)
            return [];
        return result;
    }
    
    isUserInBanList(roomname: string, userId: number) {
        if (this.banList.get(roomname) === null) return false;
        return this.banList.get(roomname).indexOf(userId) !== -1;
    }
    
    deleteBanList(roomname: string, userId: number) {
        this.banList.set(roomname,
            this.banList.get(roomname).filter(deleteId => userId !== deleteId));
    }
    
    /* MuteList */
    initMuteList(roomName: string) {
        this.muteList.set(roomName, null);
    }
    
    addMuteList(roomname: string, userId: number) {
        if (this.muteList.get(roomname) === null)
            this.muteList.set(roomname, [userId]);
        else
            this.muteList.get(roomname).push(userId);
    }
    
    isUserInMuteList(userId: number, roomname: string) {
        if (this.muteList.get(roomname) === null) return false;
        return this.muteList.get(roomname).indexOf(userId) !== -1;
    }
    
    deleteMuteList(userId: number, roomName: string) {
        if (this.isUserInMuteList(userId, roomName)) {
            if (this.muteList.get(roomName).length === 0)
                this.muteList.delete(roomName);
            else
                this.muteList.set(roomName,
                    this.muteList.get(roomName).filter(deleteName => userId !== deleteName));
        }
    }
}
