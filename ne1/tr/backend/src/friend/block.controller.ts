import { Body, Controller, Get, Param, Post, Req, Res } from "@nestjs/common";
import { FriendService } from "./friend.service";
import { BlockService } from "./block.service";

@Controller()
export class BlockController {
    constructor(private blockService: BlockService) {}
    
    @Get('/blockList/:id')
    async getAllFriend(@Param('id') id: number, @Res() res, @Req() req) {
        const result = await this.blockService.getAllBlock(id);
        res.status(200).json(result);
    }
    
    @Post('/addBlock/:id')
    async addBlock(
        @Param('id') userId: number,
        @Body('username') blockName: string,
        @Res() res,
        @Req() req
    ) {
        await this.blockService.addBlock(userId, blockName) === true ? res.status(200).json() : res.status(401).json();
    }
    
    @Post('/deleteBlock/:id')
    async deleteFriend(
        @Param('id') userId: number,
        @Body('userid') blockId: number,
        @Res() res,
        @Req() req
    ) {
        await this.blockService.deleteBlock(userId, blockId);
        res.status(200).json();
    }
}
