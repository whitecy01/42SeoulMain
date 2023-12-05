import { Body, Controller, Get, Param, Post, Req, Res } from "@nestjs/common";
import { FriendService } from "./friend.service";

@Controller()
export class FriendController {
  constructor(private friendService: FriendService) {}

  @Get('/friendsList/:id')
  async getAllFriend(@Param('id') id: number, @Res() res, @Req() req) {
    const result = await this.friendService.getAllFriend(id);
    res.status(200).json(result);
  }

  @Post('/deleteFriend/:id')
  async deleteFriend(
    @Param('id') userId: number,
    @Body('userid') friendId: number,
    @Res() res,
    @Req() req
  ) {
    await this.friendService.deleteFriend(userId, friendId);
    res.status(200).json();
  }
}
