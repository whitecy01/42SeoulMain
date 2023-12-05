import { GetUserDto } from "./get-user.dto";

export interface RestoreRoomDto {
    type: string;
    roomname: string;
    status: string,
    admin: string[];
    owner: string;
    member: GetUserDto[];
}