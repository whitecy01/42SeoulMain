import { Injectable } from '@nestjs/common';

const PlayGround = {
  WIDTH: 600,
  HEIGHT: 400,
};

class Stadium {
  width: number;
  height: number;
  constructor(width: number, height: number) {
    this.width = width;
    this.height = height;
  }
}

class GameUser {
  width: number;
  height: number;
  x: number;
  y: number;
  score: number;
  constructor(
    width: number,
    height: number,
    x: number,
    y: number,
    score: number,
  ) {
    this.width = width;
    this.height = height;
    this.x = x;
    this.y = y;
    this.score = score;
  }
}

class Ball {
  x: number;
  y: number;
  radius: number;
  speed: number;
  velocityX: number;
  velocityY: number;
  constructor(
    x: number,
    y: number,
    radius: number,
    speed: number,
    vx: number,
    vy: number,
  ) {
    this.x = x;
    this.y = y;
    this.radius = radius;
    this.speed = speed;
    this.velocityX = vx;
    this.velocityY = vy;
  }
}

class OldBall {
  updateTimeX: number;
  updateTimeY: number;
  x: number;
  y: number;
  constructor(updateTime: number, x: number, y: number) {
    this.updateTimeX = updateTime;
    this.updateTimeY = updateTime;
    this.x = x;
    this.y = y;
  }
}

export class PlayInfo {
  ball: Ball;
  oldBall: OldBall;
  user: GameUser;
  oppositeUser: GameUser;
  stadium: Stadium;
  constructor(
    ball: Ball,
    oldBall: OldBall,
    user: GameUser,
    opUser: GameUser,
    stadium: Stadium,
  ) {
    this.ball = ball;
    this.user = user;
    this.oppositeUser = opUser;
    this.stadium = stadium;
    this.oldBall = oldBall;
  }
}
@Injectable()
export class GameLogic {
  private playRooms: Map<number, PlayInfo>;
  private roomCnt: number;
  private framePerSecond: number;

  constructor() {
    this.roomCnt = 0;
    this.playRooms = new Map<number, PlayInfo>();
    this.framePerSecond = 20;
  }

  ReadyGame(num: number, updateTime: number) {
    const stadium = new Stadium(PlayGround.WIDTH, PlayGround.HEIGHT);
    const ball = new Ball(300, 200, 10, 10, 10, 10);
    const user = new GameUser(10, 100, 0, stadium.height / 2 - 100 / 2, 0);
    const opUser = new GameUser(
      10,
      100,
      stadium.width - 10,
      stadium.height / 2 - 100 / 2,
      0,
    );
    const oldBall = new OldBall(updateTime, 300, 200);
    const playInfo = new PlayInfo(ball, oldBall, user, opUser, stadium);
    this.playRooms.set(num, playInfo);
  }

  private checkCollision(ball: Ball, player: GameUser) {
    const ballTop = ball.y - ball.radius;
    const ballBottom = ball.y + ball.radius;
    const ballLeft = ball.x - ball.radius;
    const ballRight = ball.x + ball.radius;

    const playerTop = player.y;
    const playerBottom = player.y + player.height;
    const playerLeft = player.x;
    const playerRight = player.x + player.width;

    return (
      ballRight > playerLeft &&
      ballBottom > playerTop &&
      ballLeft < playerRight &&
      ballTop < playerBottom
    );
  }

  private resetBall(ball: Ball, oldBall: OldBall, stadium: Stadium) {
    ball.x = stadium.width / 2;
    ball.y = stadium.height / 2;
    ball.speed = 10;
    oldBall.x = ball.x;
    oldBall.y = ball.y;
    const nowTime = Date.now();
    oldBall.updateTimeX = nowTime;
    oldBall.updateTimeY = nowTime;
  }

  private updateGameLong({
    ball,
    oldBall,
    user,
    oppositeUser,
    stadium,
  }): PlayInfo {
    const nowTime = Date.now();
    const weightX =
      ((nowTime - oldBall.updateTimeX) * this.framePerSecond) / 1000;
    const weightY =
      ((nowTime - oldBall.updateTimeY) * this.framePerSecond) / 1000;
    if (weightX < 0) return { ball, oldBall, user, oppositeUser, stadium };
    //console.log('wx: ', weightX, 'wy: ', weightY);
    //console.log(nowTime - updateTime);
    ball.x = oldBall.x + ball.velocityX * weightX;
    ball.y = oldBall.y + ball.velocityY * weightY;

    if (ball.y + ball.radius > stadium.height) {
      if (ball.velocityY > 0) {
        ball.velocityY = -ball.velocityY;
        oldBall.updateTimeY = nowTime;
      }
      oldBall.y = ball.y + ball.velocityY;
      //console.log(ball.x, ball.y);
    }
    if (ball.y - ball.radius < 0) {
      if (ball.velocityY < 0) {
        ball.velocityY = -ball.velocityY;
        oldBall.updateTimeY = nowTime;
      }
      oldBall.y = ball.y + ball.velocityY;
      //console.log(ball.x, ball.y);
    }

    const player = ball.x < stadium.width / 2 ? user : oppositeUser;
    if (this.checkCollision(ball, player)) {
      let collidePoint = ball.y - (player.y + player.height / 2);
      collidePoint = collidePoint / (player.height / 2);
      const angleRad = (collidePoint * Math.PI) / 4;

      const direction = ball.x < stadium.width / 2 ? 1 : -1;

      if (direction === 1) ball.velocityX = ball.speed * Math.cos(angleRad);
      else ball.velocityX = -ball.speed * Math.cos(angleRad);
      ball.velocityY = ball.speed * Math.sin(angleRad);
      ball.speed += 1;
      oldBall.x = ball.x + ball.velocityX;
      oldBall.y = ball.y + ball.velocityY;
      oldBall.updateTimeX = nowTime;
      oldBall.updateTimeY = nowTime;
    } else {
      if (ball.x - ball.radius < 0) {
        oppositeUser.score++;
        ball.velocityX = 10;
        ball.velocityY = 10;
        this.resetBall(ball, oldBall, stadium);
      }
      if (ball.x + ball.radius > stadium.width) {
        user.score++;
        ball.velocityX = -10;
        ball.velocityY = 10;
        this.resetBall(ball, oldBall, stadium);
      }
    }
    return { ball, oldBall, user, oppositeUser, stadium };
  }

  checkEnd(playInfo: PlayInfo) {
    if (playInfo.user.score > 10 || playInfo.oppositeUser.score > 10) {
      if (Math.abs(playInfo.user.score - playInfo.oppositeUser.score) > 1) {
        return true;
      }
    }
    return false;
  }

  playGame({ roomNum, team, y }) {
    let playInfo = this.playRooms.get(roomNum);
    if (team == 0) playInfo.user.y = y;
    else playInfo.oppositeUser.y = y;
    playInfo = this.updateGameLong(playInfo);
    if (this.checkEnd(playInfo)) {
      return {
        red: {
          x: playInfo.user.x,
          y: playInfo.user.y,
          score: playInfo.user.score,
          height: playInfo.user.height,
          width: playInfo.user.width,
        },
        blue: {
          x: playInfo.oppositeUser.x,
          y: playInfo.oppositeUser.y,
          score: playInfo.oppositeUser.score,
          height: playInfo.oppositeUser.height,
          width: playInfo.oppositeUser.width,
        },
        ball: playInfo.ball,
        stadium: playInfo.stadium,
        winner: playInfo.user.score > playInfo.oppositeUser.score ? 0 : 1,
      };
    }
    return {
      red: {
        x: playInfo.user.x,
        y: playInfo.user.y,
        score: playInfo.user.score,
        height: playInfo.user.height,
        width: playInfo.user.width,
      },
      blue: {
        x: playInfo.oppositeUser.x,
        y: playInfo.oppositeUser.y,
        score: playInfo.oppositeUser.score,
        height: playInfo.oppositeUser.height,
        width: playInfo.oppositeUser.width,
      },
      ball: playInfo.ball,
      stadium: playInfo.stadium,
    };
  }
}
