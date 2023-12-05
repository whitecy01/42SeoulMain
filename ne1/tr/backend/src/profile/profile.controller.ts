import {
  Body,
  Controller, Param,
  Post, Req,
  Response,
  UploadedFile,
  UseInterceptors
} from "@nestjs/common";
import { ProfileService } from './profile.service';
import { FileInterceptor } from '@nestjs/platform-express';
import { ProfileValidationPipe } from './profile.validation.pipe';
import { DashBoardDto, ProfileDto } from './profile.dto';

@Controller('profile')
export class ProfileController {
  constructor(private profileService: ProfileService) {}

  // @Post('/update')
  @Post('/setUser/avatar/:id')
  @UseInterceptors(FileInterceptor('image'))
  async updateProfile(
      @Param('id') id: number,
    // @Body(ProfileValidationPipe) profileDto: ProfileDto,
    @UploadedFile() file: Express.Multer.File,
    @Response() res,
      @Req() req
  ) {
    const result = await this.profileService.updateProfile(id, file);
    res.status(200).json(result);
  }

  @Post('/dashBoard/history/:id')
  async getDashBoard(@Body() dashboardDto: DashBoardDto, @Response() res, @Req() req) {
    const result = await this.profileService.getGameHistory(
          dashboardDto.userId,
      );
    res.status(200).json(result);
  }

  @Post('/dashBoard/:id')
  async getGameProfile(@Body('userName') userName: string, @Response() res, @Req() req) {
    const result = await this.profileService.getGameProfile(
        userName
    );
    res.status(200).json(result);
  }
}
