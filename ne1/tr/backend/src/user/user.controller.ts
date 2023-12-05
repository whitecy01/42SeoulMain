import { Body, Controller, Param, Post, Req, Res } from "@nestjs/common";
import { Get } from "@nestjs/common";
import { UserService } from "./user.service";
import { User } from "./user.entity";

@Controller()
export class UserController {
    constructor(
        private userService: UserService,
    ) {}
    
    @Get('/user/:id')
    async mainUser(@Param('id') id: number, @Req() req, @Res() res) {
        const user = await this.userService.findMainUserById(id);
        res.status(200).json(user);
    }
    
    @Post('/setUser/name/:id')
    async updateUsername(@Param('id') id: number,
                         @Body('username') username: string,
                         @Res() res, @Req() req) {
        await this.userService.updateUsername(id, username, res);
        res.sendStatus(200);
    }
    
    // 이건 걍 테스트용 (나중에 삭제해도 됨)
    @Get('/test/allUser')
    getAllUsers(): Promise<User[]> {
        return this.userService.getAllUser();
    }
}
