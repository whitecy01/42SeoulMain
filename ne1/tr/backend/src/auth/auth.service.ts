import { Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { authenticator } from 'otplib';
import { User } from 'src/user/user.entity';
import { UserRepository } from 'src/user/user.repository';

@Injectable()
export class AuthService {
	constructor(
		private jwtService: JwtService,
		private userRepository: UserRepository,
	) {}

	async generateToken(username: string): Promise<{accessToken: string}> {
		const payload = { username: username };
		const accessToken = this.jwtService.sign(payload);

		return { accessToken }
	}

	public generateTwoFactorAuthSecret(user: User) {
		if (!user.secretKey)
		{
			user.secretKey = authenticator.generateSecret();
			this.userRepository.saveUser(user);
		}
		const otpAuthUrl = authenticator.keyuri('', '', user.secretKey);

		return otpAuthUrl;
	}

	public async isTwoFactorAuthCodeValid(secretKey: string, twoFactorAuthCode: string) {
		return authenticator.verify({
			token: twoFactorAuthCode,
			secret: secretKey,
		})
	}
}
