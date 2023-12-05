import { Body, Controller, Get, HttpStatus, Post, Query, Request, Response, UnauthorizedException, UseGuards } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthGuard } from '@nestjs/passport';
import { UserService } from 'src/user/user.service';
import { UserRepository } from 'src/user/user.repository';
import { ConnectedSockets } from 'src/socket/connected-sockets.service';

@Controller('auth')
export class AuthController {
	constructor(
		private readonly authService: AuthService,
		private readonly userService: UserService,
		private readonly userRepository: UserRepository,
		private readonly connectSockets: ConnectedSockets,
		) {}

	@Get('42login')
	@UseGuards(AuthGuard('ft'))
	userLogin(@Request() req) {
	}

	@Get('redirect')
	@UseGuards(AuthGuard('ft'))
	async redirect(@Request() req, @Response() res) {
		const accessToken = await this.authService.generateToken(req.user);
		const user = await this.userService.createUser(req.user, accessToken.accessToken);
		if (this.connectSockets.hasUserId(user.id))
			return res.status(HttpStatus.BAD_REQUEST).redirect(`${process.env.FRONT_URL}`);
		if (user.twofactorauth && !user.istwofactorauth)
			res.redirect(`${process.env.FRONT_URL}/fa2?id=${user.id}`);
		else
			res.redirect(`${process.env.FRONT_URL}/callback?id=${user.id}`);
	}
	
	@Post('getOtpAuthUrl')
	async getOtpAuthUrl(@Response() res, @Body('id') id: number) {
		const user = await this.userRepository.findUserById(id);
		const otpAuthUrl = await this.authService.generateTwoFactorAuthSecret(user);
		res.json({
			id: id,
			otpAuthUrl
		});
	}

	@Post('verify')
	async verify(
		@Response() res,
		@Query('twoFactorAuthCode') twoFactorAuthCode: string,
		@Body('id') id: number
		) {
		const user = await this.userRepository.findUserById(id);
		const isCodeValidated = await this.authService.isTwoFactorAuthCodeValid(
			user.secretKey,
			twoFactorAuthCode
			);
		if (!isCodeValidated)
			res.status(HttpStatus.BAD_REQUEST).json({ id: id });
		else
		{
			user.istwofactorauth = true;
			await this.userRepository.saveUser(user)
			res.status(HttpStatus.OK).json({ id: id });
		}
	}

	@Post('getToken')
	async getToken(@Response() res, @Body('id') id: number) {
		const user = await this.userRepository.findUserById(id);
		let register = false;
		if (!user.username)
			register = true;
		res.json({
			id: user.id,
			token: user.token,
			register: register,
		});
	}

	@Post('twoFactorAuthSwitch')
	async twoFactorAuthSwitch(
		@Response() res,
		@Body('twoFactorAuth') twoFactorAuth: string,
		@Body('userId') id: number
		) {
		const user = await this.userRepository.findUserById(id);
		if (twoFactorAuth === 'on')
			user.twofactorauth = true;
		else
			user.twofactorauth = false;
		this.userRepository.saveUser(user);

		res.status(HttpStatus.OK).json({
			id: id,
			twoFactorAuth: user.twofactorauth
		});
	}

	@Get('42logout')
	async userLogout(@Response() res, @Query('id') id: number) {
		const user = await this.userRepository.findUserById(id);
		user.istwofactorauth = false;
		await this.userRepository.saveUser(user);
		res.status(HttpStatus.OK).send("logout success");
	}
}
