export interface ExitRoomDto {
    // changeAdmin: boolean;
    changeOwner: boolean;
    roomname: string;
    username: string;
    userId: number;
    admin: string[];
    owner: string;
}