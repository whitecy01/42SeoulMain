import { UserStatus } from "../user/user-status.enum";
import { Game } from "../game/game.entity";

export class DummyDto {
    token: string;
    intraId: string;
    username: string;
    avatar: string;
    game: Game;
    status: UserStatus;

    constructor(token: string, intraId: string, username: string, avatar: string, game: Game, status: UserStatus) {
        this.token = token;
        this.intraId = intraId;
        this.username = username;
        this.avatar = avatar;
        this.game = game;
        this.status = status;
    }
}