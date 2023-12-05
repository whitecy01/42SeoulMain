import { Body, Controller, Get, Param, Post, Req, Res } from "@nestjs/common";
import { BanListService } from "./ban.service";

@Controller()
export class BanController {
    constructor(
        private banListService: BanListService
    ) {}
    
    @Get('/banList/:roomname/:id')
    async getBanList(@Param('roomname') roomname: string,
                     @Req() req, @Res() res) {
        const result = await this.banListService.getBanList(roomname);
        res.status(200).json(result);
    }
    
    @Post('/cancelBan/:id')
    async cancelBanList(@Body('roomname') roomname: string,
                        @Body('userTo') userTo: number,
                        @Res() res, @Req() req) {
        await this.banListService.cancelBanList(roomname, userTo, res);
        res.status(200).json();
    }
}
