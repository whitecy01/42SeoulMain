import { Controller, Get, Post } from '@nestjs/common';
import { UserService } from './user.service';

@Controller({ host: 'init.localhost' })
export class InitController {
  constructor(private userService: UserService) {}

  @Get()
  initUser() {
    this.userService.initUser();
    return 'success!';
  }
}
