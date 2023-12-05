const cvs = document.getElementById('pong');
const ctx = cvs.getContext('2d');

function drawRect(x, y, w, h, color) {
  ctx.fillStyle = color;
  ctx.fillRect(x, y, w, h);
}

//draw Circle
function drawCircle(x, y, r, color) {
  ctx.fillStyle = color;
  ctx.beginPath();
  ctx.arc(x, y, r, 0, 2 * Math.PI, false);
  ctx.closePath();
  ctx.fill();
}

//draw Text
function drawText(text, x, y, color) {
  ctx.fillStyle = color;
  ctx.font = '45px fantasy';
  ctx.fillText(text, x, y);
}

//create the user paddle
const user = {
  width: 10,
  height: 100,
  x: 0,
  y: cvs.height / 2 - 100 / 2,
  color: 'WHITE',
  score: 0,
};

const com = {
  width: 10,
  height: 100,
  x: cvs.width - 10,
  y: cvs.height / 2 - 100 / 2,
  color: 'WHITE',
  score: 0,
};

//create the ball
const ball = {
  x: cvs.width / 2,
  y: cvs.height / 2,
  radius: 10,
  speed: 10,
  velocityX: 10,
  velocityY: 10,
  color: 'WHITE',
};

//create the net
const net = {
  x: cvs.width / 2 - 1,
  y: 0,
  width: 2,
  height: 10,
  color: 'WHITE',
};

function drawNet() {
  for (let idx = 0; idx <= cvs.height; idx += 15) {
    drawRect(net.x, net.y + idx, net.width, net.height, net.color);
  }
}

function render() {
  //clear the canvas
  drawRect(0, 0, cvs.width, cvs.height, 'BLACK');

  //draw the net
  drawNet();

  //draw score
  drawText(user.score, cvs.width / 4, cvs.height / 5, 'WHITE');
  drawText(com.score, (cvs.width * 3) / 4, cvs.height / 5, 'WHITE');

  // draw the user and com paddle
  drawRect(user.x, user.y, user.width, user.height, user.color);
  drawRect(com.x, com.y, com.width, com.height, com.color);

  //draw the ball
  drawCircle(ball.x, ball.y, ball.radius, 'WHITE');
}

function ReturnRender(data) {
  //clear the canvas
  console.log('asjdlfjlasjdklfj');
  drawRect(0, 0, data.stadium.width, data.stadium.height, 'BLACK');

  //draw the net
  drawNet();

  //draw score
  drawText(
    data.red.score,
    data.stadium.width / 4,
    data.stadium.height / 5,
    'WHITE',
  );
  drawText(
    data.blue.score,
    (data.stadium.width * 3) / 4,
    data.stadium.height / 5,
    'WHITE',
  );

  drawRect(data.red.x, data.red.y, data.red.width, data.red.height, 'WHITE');
  drawRect(
    data.blue.x,
    data.blue.y,
    data.blue.width,
    data.blue.height,
    'WHITE',
  );

  //draw the ball
  drawCircle(data.ball.x, data.ball.y, data.ball.radius, 'WHITE');
}

//collision detection
function collision(ball, player) {
  ball.top = ball.y - ball.radius;
  ball.bottom = ball.y + ball.radius;
  ball.left = ball.x - ball.radius;
  ball.right = ball.x + ball.radius;

  player.top = player.y;
  player.bottom = player.y + player.height;
  player.left = player.x;
  player.right = player.x + player.width;

  return (
    ball.right > player.left &&
    ball.bottom > player.top &&
    ball.left < player.right &&
    ball.top < player.bottom
  );
}

//control the user paddle
cvs.addEventListener('mousemove', movePaddle);

function movePaddle(evt) {
  let rect = cvs.getBoundingClientRect();

  user.y = evt.clientY - rect.top - user.height / 2;
}

//reset the ball
function resetBall() {
  ball.x = cvs.width / 2;
  ball.y = cvs.height / 2;
  ball.speed = 5;
}

//update : pos, mov, score, .....
async function update() {
  ball.x += ball.velocityX;
  ball.y += ball.velocityY;

  let computerLevel = 0.1;
  com.y += (ball.y - (com.y + com.height / 2)) * computerLevel;

  if (ball.y + ball.radius > cvs.height || ball.y - ball.radius < 0) {
    ball.velocityY = -ball.velocityY;
  }

  let player = ball.x < cvs.width / 2 ? user : com;
  if (collision(ball, player)) {
    //where the ball hit
    let collidePoint = ball.y - (player.y + player.height / 2);
    // normalization
    collidePoint = collidePoint / (player.height / 2);
    //calculate angle in Radian

    let angleRad = (collidePoint * Math.PI) / 4;

    // x direction of the ball when it's hit
    let direction = ball.x < cvs.width / 2 ? 1 : -1;

    //change vel x and y
    if (direction === 1) ball.velocityX = ball.speed * Math.cos(angleRad);
    else ball.velocityX = -ball.speed * Math.cos(angleRad);
    ball.velocityY = ball.speed * Math.sin(angleRad);

    //every time the ball hit a paddle, we encrease its speed
    ball.speed += 2;
  } else {
    //update the score
    if (ball.x - ball.radius < 0) {
      com.score++;
      ball.velocityX = 5;
      ball.velocityY = 5;
      resetBall();
    } else if (ball.x + ball.radius > cvs.width) {
      user.score++;
      ball.velocityX = -5;
      ball.velocityY = 5;
      resetBall();
    }
  }
}

function game() {
  update();
  render();
}

const socket = io('http://localhost:3000/game', {
  withCredentials: true,
});
let roomNum;
let team;
let intervalId;
let userId;
let winner;

socket.on('connect', () => {
  console.log('connected');
  sendReady();
});

socket.on('position', (message) => {
  console.log('x : ', message.x, 'y: ', message.y);
});

const framePerSecond = 20;

socket.on('setGame', (data) => {
  console.log('set');
  roomNum = data.roomNum;
  team = data.team;
  intervalId = setInterval(sendPosition, 1000 / framePerSecond);
});

socket.on('updateGame', (data) => {
  ReturnRender(data);
});

socket.on('timeOutGame', () => {
  console.log('timeOut!!!!');
  clearInterval(intervalId);
  intervalId = null;
  socket.disconnect();
});

socket.on('endGame', (data) => {
  console.log(data.winner);
  winner = data.winner;
  clearInterval(intervalId);
  intervalId = null;
  sendSave();
});

function sendSave() {
  console.log('save');
  socket.emit('saveGame', {
    userId: userId,
    roomNum: roomNum,
    team: team,
    winner: winner,
  });
  socket.disconnect();
}

socket.on('disconnect', () => {
  clearInterval(intervalId);
  intervalId = null;
  console.log('연결 끊김');
});

socket.on('sendReady', () => {
  clearInterval(intervalId);
  console.log('get SendReadyMessage');
});

function sendPosition() {
  console.log(roomNum, team, user.y);
  socket.emit('playGame', { roomNum: roomNum, team: team, y: user.y });
}

function sendReady() {
  userId = (parseInt(String(Math.random() * 1000000), 10) % 4) + 1;
  console.log('userID: ', userId);
  socket.emit('readyGame', { userId: userId });
}
