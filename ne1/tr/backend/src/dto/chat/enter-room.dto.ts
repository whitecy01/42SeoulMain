import { GetUserDto } from "./get-user.dto";

export interface EnterRoomDto {
    userIdTo: number;
    usernameFrom: string;
    roomName: string;
    status : string;
    admin : string[];
    owner : string;
    members : GetUserDto[];
}