import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-42';
import axios from 'axios';
import { UserService } from 'src/user/user.service';
import { UserRepository } from 'src/user/user.repository';
import { AuthService } from '../auth.service';

@Injectable()
export class FtStrategy extends PassportStrategy(Strategy, 'ft') {
  constructor(
    configService: ConfigService,
    ) {
    super({
      clientID: configService.get<string>("CLIENT_ID"),
      clientSecret: configService.get<string>("CLIENT_SECRET"),
      callbackURL: configService.get<string>("CALLBACK_URL"),
    });
  }

  async validate(accessToken: string, refreshToken: string) {
    try {
      const req = await axios.get('https://api.intra.42.fr/v2/me', {
        headers: { Authorization: `Bearer ${accessToken}` },
      });

      return req.data.login;
    } catch (error) {
      console.log(error);
    }
  }
}