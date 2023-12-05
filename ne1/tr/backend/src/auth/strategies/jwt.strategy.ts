import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { UserRepository } from 'src/user/user.repository';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
	constructor(private readonly userRepository: UserRepository) {
		super({
			secretOrKey: process.env.KEY,
			jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken()
		})
	}

	async validate(payload) {
		const { username } = payload;
		const user = await this.userRepository.findUserByIntraId(username);
		if (!user)
			throw new UnauthorizedException();
	}
}