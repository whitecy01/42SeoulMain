<template>
    <div ref="childDiv" id="gamecontainer">
        <canvas id="game" ref="canvasRef" tabindex="1"></canvas>
        <div class= "gamebutton" v-if="gameStatus === 'start'" @click="ReadyGame">
            <img src="/gamestart_img.png">
            <img src="/GameStart.png" >
        </div>
        <div v-if="gameStatus === 'ready'" class="loadding">
            <img src="/loadding.gif" class="loadding-img">
            <div class="matchuser"> 1 / 2 </div>
            <div class="button-box">
                <div class="cancel-bt" @click="cancelGame"> 취소하기</div>
                <div class="ai-mode" @click="AiStartGame"> 연습모드 </div>
            </div>
        </div>
        <div v-if="gameStatus === 'AIend' || gameStatus === 'end' || gameStatus === 'timeOut'" class="loadding">
            <div class="button-box">
                <div class="cancel-bt" @click="resetGame">돌아가기</div>
            </div>
        </div>
    </div>
</template>

<script setup lang="ts">
    import { ref, onMounted, onUnmounted, computed, watch} from 'vue';
    import { useSocketStore } from '@/store/socket'
    import { usePopupStore } from '@/store/status';

    const childDiv = ref<HTMLElement | null>(null);

    const emit = defineEmits(["updateHeight"]);

    function emitHeight() {
    if (childDiv.value) {
        const height = childDiv.value.offsetHeight;
        emit('updateHeight', height);
    }
    }
    const socketStore = useSocketStore();
    
    const popupstore = usePopupStore();

    const canvasRef = ref<HTMLCanvasElement | null>(null);

    let canvas = canvasRef.value;

    let ctx: CanvasRenderingContext2D | null = null;

    let intervalID :number;

    interface Ball {
        x: number;
        y: number;
        radius: number;
        velocityX: number;
        velocityY: number;
        color: string;
        top : number;
        bottom : number;
        left : number;
        right : number;
    }

    interface Player {
        x : number;
        y : number;
        width : number;
        height : number;
        ballspeed : number;
        score : number;
        color : string,
        top : number;
        bottom : number;
        left : number;
        right : number;
    }

    interface Game {
        end : boolean;
        match : boolean;
        winner : string;
    }

    const ball : Ball = {
        x : 0, 
        y : 0,
        radius : 10,
        velocityX : 5,
        velocityY : 0,
        color : "WHITE",
        top : 0,
        bottom : 0,
        left : 0,
        right : 0
    }

    const user : Player= {
        x : 0,
        y : 0,
        width : 10,
        height : 100,
        ballspeed : 7,
        score : 0,
        color : "red",
        top : 0,
        bottom : 0,
        left : 0,
        right : 0
    }

    const net = {
        x : 0,
        y : 0,
        height : 50,
        width : 5,
        color : "WHITE"
    }
    
    const com : Player = {
        x : 0,
        y : 0,
        width : 10,
        height : 100,
        ballspeed : 7,
        score : 0,
        color : "blue",
        top : 0,
        bottom : 0,
        left : 0,
        right : 0
    }

    const game : Game = {
        end : false,
        match : false,
        winner : ''
    }

    const resetwindow = (me : Player, you : Player) =>
    {
        if(canvas)
        {
            if(popupstore.game.gamestatus === 'ai')
            {
                me.x = 0;
                me.color = 'Red';
                you.color = 'blue';
            }
            me.y = (canvas.height - me.height)/2;
            you.x = canvas.width - you.width;
            you.y = (canvas.height - you.height)/2;
            net.x = (canvas.width - 2)/2;
            me.score = 0;
            you.score = 0;
            resetBall();
        }
    }
    
    const drawArc = (x : number, y : number, r : number, color : string) => {
        if (ctx)
        {
            ctx.fillStyle = color;
            ctx.beginPath();
            ctx.arc(x,y,r,0,Math.PI*2,true);
            ctx.closePath();
            ctx.fill();
        }
    }

    const resetBall = () => {
        if(canvas){
            ball.x = canvas.width/2;
            ball.y = canvas.height/2;
            ball.velocityX = -ball.velocityX / ball.velocityX * 5;
            ball.velocityY = 0;
            user.ballspeed = 7;
        }
    }

    const drawRect = (x: number, y: number, w: number, h: number, color: string) => {
    if (ctx) {
        ctx.fillStyle = color;
        ctx.fillRect(x, y, w, h);
    }
    };

    const drawNet = () => {
        if(canvas){
        for(let i = 0; i <= canvas.height; i += net.height*1.5){
            drawRect(net.x, net.y + i, net.width, net.height, net.color);
        }}
    }
    const drawText = (text : string, x : number, y : number, font : string, color : string) => {
        if (ctx) {
            ctx.fillStyle = color;
            ctx.font = font;
            ctx.fillText(text, x, y);
        }
    }

    const collision = (b : Ball, p : Player) => {
        p.top = p.y;
        p.bottom = p.y + p.height;
        p.left = p.x;
        p.right = p.x + p.width;
        
        b.top = b.y - b.radius;
        b.bottom = b.y + b.radius;
        b.left = b.x - b.radius;
        b.right = b.x + b.radius;
        
        return p.left < b.right && p.top < b.bottom && p.right > b.left && p.bottom > b.top;
    }

    const endcheck = () => {

        if (user.score >= 11)
        {
            if(user.score >= com.score + 2)
            {
                game.winner = 'User'
                return true;
            }
            else
                game.match = true;
        }
        else if (com.score >= 11)
        {
            if(com.score >= user.score + 2)
            {
                game.winner = 'Com'
                return true;
            }
            else
                game.match = true;
        }
        return false;
    }

    const update = () => {
        if (canvas){
        if( ball.x - ball.radius < 0 ){
            com.score++;
            resetBall();
        }else if( ball.x + ball.radius > canvas.width){
            user.score++;
            resetBall();
        }
        if(endcheck())
        {
            game.end = true;
            if(intervalID !== 0)
            {
                clearInterval(intervalID);
                intervalID = 0;
            }
            popupstore.setGameStatus('AIend');
            return ;
        }
        ball.x += ball.velocityX;
        ball.y += ball.velocityY;
    
        // simple AI
        com.y += ((ball.y - (com.y + com.height/2)))*0.05;
    
        // attack wall
        if(ball.y - ball.radius < 0 || ball.y + ball.radius > canvas.height){
            ball.velocityY = -ball.velocityY;
        }
    
        // we check if the paddle hit the user or the com paddle
        let player = (ball.x + ball.radius < canvas.width/2) ? user : com;
        
        // if the ball hits a paddle
        if(collision(ball,player)){

            let collidePoint = (ball.y - (player.y + player.height/2));
            collidePoint = collidePoint / (player.height/2);
            
            let angleRad = (Math.PI/4) * collidePoint;
        
            let direction = (ball.x + ball.radius < canvas.width/2) ? 1 : -1;
            ball.velocityX = direction * player.ballspeed * Math.cos(angleRad);
            ball.velocityY = player.ballspeed * Math.sin(angleRad);
            player.ballspeed = 7;
        }}
    }

    const clearCanvas = () =>{
        if(canvas && ctx)
            ctx.clearRect(0, 0, canvas.width, canvas.height);
    }


    const Drawend = () => {
        
        if (canvas){
            clearCanvas();
            const myScore = popupstore.game.team == 0 ? 60 : -60;
            const widthratio = canvas.width / popupstore.game.width;
            const fontsize = 50 * widthratio;
            if(game.winner === 'Server TimeOut')
            {
                drawText( game.winner , canvas.width/4 -50, canvas.height/5,`${fontsize}px sansation_Bold`,"#FFF");
            }
            else {
                drawText('Winer ' + game.winner , canvas.width/3 -50, canvas.height/5,`${fontsize}px sansation_Bold`,"#FFF");
                drawText(String(user.score), canvas.width/2 - (myScore) ,canvas.height/3, `${fontsize/2}px sansation_Bold`,'white');
                drawText(" : ", canvas.width/2,canvas.height/3, `${fontsize/2}px sansation_Bold`,'white');
                drawText(String(com.score), canvas.width/2 - (-myScore),canvas.height/3, `${fontsize/2}px sansation_Bold`,'white');
            }
        }

    }

    const render = () => {
        if(canvas)
        {
            if(game.end)
                Drawend();
            else
            {
                const redScore = popupstore.game.team === 0 ? user.score : com.score;
                const blueScore = popupstore.game.team === 1 ? user.score : com.score;
                const widthratio = canvas.width / popupstore.game.width;
                const fontsize = 75 * widthratio;
                // clear the canvas
                drawRect(0, 0, canvas.width, canvas.height, "#000");
                
                // draw the user score to the left
                drawText(String(redScore),canvas.width/4,canvas.height/5, `${fontsize}px sansation_Bold`, 'Red');
                
                // draw the COM score to the right
                drawText(String(blueScore),3*canvas.width/4,canvas.height/5,`${fontsize}px sansation_Bold`, 'blue');
                //match
                if(game.match)
                    drawText('Match', canvas.width/2, 30, `${fontsize/3}px sansation_Bold`,"#FFF");
                //net
                drawNet();

                drawRect(user.x, user.y, user.width, user.height, user.color);
                drawRect(com.x, com.y, com.width, com.height, com.color);
                //ball
                drawArc(ball.x, ball.y, ball.radius, ball.color);
            }
        }
    }

    const AiPlaygame = () => {
        update();
        render();
    }

    const getMousePos = (event : MouseEvent) => {
        if (canvas)
        {
            const heightratio = canvas.height / popupstore.game.height;
            let rect = canvas.getBoundingClientRect();
            user.y = event.clientY - rect.top - user.height/2;
            if(popupstore.game.gamestatus === 'play')
                popupstore.setServerY(user.y/heightratio);
        }
    }

    const getBallSpeed =(event : KeyboardEvent) => {
        if (canvas)
        {
            if (event.key == ' ' && user.ballspeed <= 10)
            {
                user.ballspeed += 0.5;
            }
        }
    }

    const resizeobject = () => {
        if (canvas)
        {
            const widthratio = canvas.width / popupstore.game.width;
            const heightratio = canvas.height / popupstore.game.height;
            const paddlewid = popupstore.game.me.width * widthratio;
            const paddlehei = popupstore.game.me.height * heightratio;

            user.width = paddlewid;
            user.height = paddlehei;
            com.width = paddlewid;
            com.height = paddlehei;
            if(popupstore.game.gamestatus === 'ai')
                com.x = canvas.width - paddlewid;
            net.width = 5 * widthratio;
            net.height = 50 * heightratio;
            net.x = canvas.width/2 - net.width;
            ball.radius = popupstore.game.ball.radius * widthratio;
        }

    }

    const canvasresize = () => {
        if (canvasRef.value)
        {
            if(canvas){
                canvas.width = canvasRef.value.offsetWidth;
                canvas.height = canvasRef.value.offsetHeight;
                emitHeight();
                resizeobject();
            }
        }
    }

    const AiStartGame = () => {
        socketStore.socketOffGameUpdate();
        socketStore.socketOffEndGame();
        socketStore.cancelGame();
        if (canvas) {
            popupstore.setGameStatus('ai');
            game.end = false;
            game.winner = '';
            game.match = false;
            canvasresize();
            resetwindow(user, com);
            canvas.addEventListener("mousemove", getMousePos);
            canvas.addEventListener("keydown", getBallSpeed);
            intervalID = setInterval(() => {AiPlaygame()}, 1000/60);
        }
    }
// main Game 로직


    popupstore.setGameStatus('start');

    const gameStatus = computed(() => popupstore.getGameStatus);
    
    const ReadyGame = () => {
        popupstore.setGameStatus('ready');
        socketStore.matchGame();
        socketStore.socketOnPlayGame();
        socketStore.socketOnEndGame();
        socketStore.socketOnTimeout();
    }

    const cancelGame = () => {
        socketStore.socketOffGameUpdate();
        socketStore.socketOffEndGame();
        socketStore.socketOffTimeout();
        socketStore.cancelGame();
        popupstore.setGameStatus('start');
    }

    const resetGame = () => {
        if(canvas)
            drawRect(0, 0, canvas.width, canvas.height, "#000");
        popupstore.setGameStatus('start');
    }

    const updateObj = () => {
        if(canvas)
        {
            const widthratio = canvas.width / popupstore.game.width;
            const heightratio = canvas.height / popupstore.game.height;
            
            user.x = popupstore.game.me.x * widthratio;
            user.score = popupstore.game.me.score;
            if(popupstore.game.team == 1)
            {
                user.color = 'blue';
                com.color = 'red';
            }
            else {
                user.color = 'red';
                com.color = 'blue'; 
            }
            com.x = popupstore.game.you.x * widthratio;
            com.y = popupstore.game.you.y * heightratio;
            com.score = popupstore.game.you.score;

            ball.x = popupstore.game.ball.x * widthratio;
            ball.y = popupstore.game.ball.y * widthratio;
            ball.radius = popupstore.game.ball.radius * ((heightratio));
        }
    }

    const Playgame = () => {
        socketStore.sendGameStatus();
        updateObj();
        render();
    }

    watch(() => popupstore.getGameStatus,
        (newStatus) =>  {
            if(newStatus === 'play')
            {
                if (canvas) {
                    game.end = false;
                    game.winner = '';
                    game.match = false;
                    canvasresize();
                    resetwindow(user, com);
                    canvas.addEventListener("mousemove", getMousePos);
                    intervalID = setInterval(() => {Playgame()}, 1000/popupstore.game.framePerSecond);
                    socketStore.socketOnGameUpdate();
                }
            }
            else if (newStatus === 'end')
            {
                if(intervalID != 0)
                {
                    clearInterval(intervalID);
                    intervalID = 0;
                }
                game.end = true;
                game.winner = popupstore.getWinner;
                updateObj();
                render();
                socketStore.socketOffGameUpdate();
                socketStore.socketOffEndGame();
                socketStore.socketOffTimeout();
            }
            else if (newStatus === 'timeOut')
            {
                if(intervalID != 0)
                {
                    clearInterval(intervalID);
                    intervalID = 0;
                }
                game.end = true;
                game.winner = 'Server TimeOut';
                updateObj();
                render();
                socketStore.socketOffGameUpdate();
                socketStore.socketOffEndGame();
                socketStore.socketOffTimeout();
            }
        }
    );

    onMounted(() => {
        if (canvasRef.value) {
            canvas = canvasRef.value;
            ctx = canvasRef.value.getContext('2d');
            if(ctx)
            {
                ctx.textAlign = "center";
                ctx.textBaseline = "middle";
                emitHeight();
                window.addEventListener("resize", canvasresize);
            }
        }
    });

    onUnmounted(() => {
        if(intervalID)
        {
            clearInterval(intervalID);
            intervalID = 0;
        }
        if(canvas)
        {
            canvas.removeEventListener("mousemove", getMousePos);
            canvas.removeEventListener("keydown", getBallSpeed);
        }
        window.removeEventListener("resize", canvasresize);
    });

</script>

<style scoped>
#gamecontainer {
    position: relative;
    display: flex;
    width: 65vw;
    height: calc(65vw * 8 / 12);
    min-width: 700px;
    min-height: 500px;
    justify-content: center;
    align-items: center;
    box-shadow: 2px 2px 2px 2px rgb(191, 191, 191);
    background-color: aqua;
}

#game {
    position: absolute;
    width: 100%;
    height: 100%;
    background-color: black;
}

.loadding {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    z-index: 1;

}

.loadding-img {
    width: 40px;
    height: 40px;
    z-index: 1;
}

.matchuser {
    display: flex;
    margin-top: 10px;
    font-size: 18px;
    color: white;
    z-index: 1;
}

.gamebutton {
    display: flex;
    flex-direction: column;
    z-index: 1;
    width: 30%;
}
.button-box {
    display: flex;
    flex-direction: column;
    margin-top: 10px;
}
.cancel-bt {
    display: flex;
    width: 100px;
    height: 30px;
    border-radius: 10px;
    align-items: center;
    justify-content: center;
    background-color: #3c3c3c;
    color: white;
}
.cancel-bt:hover {
    background-color: #B61A1A;
}

.ai-mode {
    display: flex;
    width: 100px;
    height: 30px;
    border-radius: 10px;
    align-items: center;
    justify-content: center;
    background-color: #3c3c3c;
    color: white;
    margin-top: 10px;
}

.ai-mode:hover{
    background-color: #265196;
}

</style>