import { Body, Controller, Get, Param, Post, Req, Res } from "@nestjs/common";
import { CreateRoomDto } from "../dto/chat/create-room.dto";
import { RoomService } from "./room.service";

@Controller()
export class RoomController {
    constructor(
        private roomService: RoomService
    ) {}

    @Post('/createRoom')
    async createRoom(@Body() createRoomDto: CreateRoomDto,
               @Res() res, @Req() req) {
        const result = await this.roomService.createRoom(createRoomDto, res);
        res.status(200).json(result);
    }
    
    @Post('/enterRoom')
    async enterRoom(@Body('userId') userId: number,
                    @Body('chennelName') roomname: string,
                    @Body('password') password: string,
                    @Req() req, @Res() res) {
        await this.roomService.enterRoomPost(userId, roomname, password) === true ?
        res.status(200).json() : res.status(401).json();
    }
    
    @Post('/changePassword/:id')
    async updatePassword(@Body('roomname') roomname: string,
                         @Body('password') pw: string,
                         @Res() res, @Req() req) {
        await this.roomService.changePw(roomname, pw);
        res.status(200).json();
    }

    @Get('/ChennelList/:id')
    async getAllRooms(@Res() res, @Req() req) {
        const result = await this.roomService.ChennelList();
        res.status(200).json(result);
    }

    // 수정요구사항 - 2번 해결
    @Post('/updateMember/:id')
    async updateMember(@Body('roomname') roomname: string,
                       @Res() res, @Req() req) {
        const result = await this.roomService.getMembers(roomname);
        res.status(200).json(result);
    }

    @Post('/muteUser/:id')
    async banUser(@Body('userTo') userTo: number,
            @Body('chennelName') roomName: string,
            @Res() res,
            @Req() req) {
        const result = this.roomService.muteUser(userTo, roomName, res);
        res.status(200).json(result);
    }
    
    @Post('/room/banDelete/:id')
    async banDelete(@Param('id') userId: number,
                    @Req() req, @Res() res) {
        const result = this.roomService.deleteMute(userId);
        res.status(200).json(result);
    }
}
