<template>
    <div ref="childDiv" id="gamecontainer">
        <canvas id="game" ref="canvasRef" tabindex="1"></canvas>
        <div class= "gamebutton" v-if="gameStat === 'start'" @click="ReadyGame">
            <img src="/gamestart_img.png">
            <img src="/GameStart.png" >
        </div>
        <div v-if="gameStat === 'ready'" class="loadding">
            <img src="/loadding.gif" class="loadding-img">
            <div class="matchuser"> 1 / 2 </div>
            <div class="button-box">
                <div class="cancel-bt" @click="cancelGame"> 취소하기</div>
                <div class="ai-mode" @click="AiStartGame"> 연습모드 </div>
            </div>
        </div>
        <div v-if="gameStat === 'AIend' || gameStat === 'end' || gameStat === 'timeOut'" class="loadding">
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
    import * as THREE from 'three';
    import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';


    const childDiv = ref<HTMLElement | null>(null);
    const emit = defineEmits(["updateHeight"]);

    let intervalID :number;

    let animateID : number;

    function emitHeight() {
        if (childDiv.value) {
            const height = childDiv.value.offsetHeight;
            emit('updateHeight', height);
        }
    }

    const canvasRef = ref<HTMLCanvasElement | null>(null);

    let canvas = canvasRef.value;

    const scoreCanvas = document.createElement('canvas');

    const context = scoreCanvas.getContext('2d');

    const texture = new THREE.CanvasTexture(scoreCanvas);

    scoreCanvas.width = 500;

    scoreCanvas.height = 150;

    let score = '';

    if (context)
    {
        context.font = '100px Arial';
        context.fillStyle = 'white';
        context.textAlign = 'center';
        context.textBaseline = 'middle';
    }

    const updateCanvasText = (text :string) => {
        if(context)
        {
            context.clearRect(0, 0, scoreCanvas.width, scoreCanvas.height);
            if(text == 'Server TimeOut')
                context.font = '60px Arial';
            else
                context.font = '100px Arial';
            context.fillText(text, scoreCanvas.width / 2, scoreCanvas.height / 2);
        }
    }

    const GameTable = {
        width :600,
        height :400
    }

    let scene: THREE.Scene;

    let camera: THREE.PerspectiveCamera;

    let renderer: THREE.WebGLRenderer;

    let player1Bar: THREE.Mesh;

    let player2Bar: THREE.Mesh;

    let gameBall: THREE.Mesh;

    let table : THREE.Mesh;

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
        x : 300, 
        y : -200,
        radius : 8,
        velocityX : 5,
        velocityY : 0,
        color : "WHITE",
        top : 0,
        bottom : 0,
        left : 0,
        right : 0
    }

    const user : Player= {
        x : 10,
        y : -200,
        width : 20,
        height : 100,
        ballspeed : 7,
        score : 0,
        color : "WHITE",
        top : 0,
        bottom : 0,
        left : 0,
        right : 0
    }
    
    const com : Player = {
        x : 590,
        y : -200,
        width : 20,
        height : 100,
        ballspeed : 7,
        score : 0,
        color : "WHITE",
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
                me.x = (me.width/2);
                me.color = 'Red';
                you.color = 'blue';
            }
            me.y = 0;
            you.x = GameTable.width - you.width/2;
            you.y = 0;
            me.score = 0;
            you.score = 0;
            resetBall();
        }
    }

    const resetBall = () => {
        if(canvas){
            ball.x = GameTable.width/2;
            ball.y = -GameTable.height/2;
            ball.velocityX = -ball.velocityX / ball.velocityX * 5;
            ball.velocityY = 0;
            user.ballspeed = 7;
        }
    }

    const collision = (b : Ball, p : Player) => {
        p.top = p.y + p.height/2;
        p.bottom = p.y - p.height/2;
        p.left = p.x - p.width/2;
        p.right = p.x + p.width/2;
        
        b.top = b.y + b.radius;
        b.bottom = b.y - b.radius;
        b.left = b.x - b.radius;
        b.right = b.x + b.radius;

        return p.left < b.right && p.top > b.bottom && p.right > b.left && p.bottom < b.top;
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
        }else if( ball.x + ball.radius > GameTable.width){
            user.score++;
            resetBall();
        }
        getScoreString();
        if(endcheck())
        {
            game.end = true;
            popupstore.setGameStatus('AIend');
            return ;
        }
        ball.x += ball.velocityX;
        ball.y += ball.velocityY;
    
        // simple AI
        com.y += ((ball.y - com.y)*0.07);
        if (com.y > -com.height/2)
            com.y = -com.height/2;
        else if (com.y < -GameTable.height + com.height/2)
            com.y = -GameTable.height + com.height/2;

        // attack wall
        if(ball.y - ball.radius < -GameTable.height || ball.y + ball.radius > 0){
            ball.velocityY = -ball.velocityY;
        }
        let player = (ball.x  - ball.radius < GameTable.width/2) ? user : com;
        
        if(collision(ball, player)){
            let collidePoint = (ball.y - player.y);

            collidePoint = collidePoint / (player.height/2);
            
            let angleRad = (Math.PI/4) * collidePoint;
        
            let direction = (ball.x + ball.radius < GameTable.width/2) ? 1 : -1;

            ball.velocityX = direction * player.ballspeed * Math.cos(angleRad);
            ball.velocityY = player.ballspeed * Math.sin(angleRad);
            player.ballspeed = 7;
        }}
    }



    const Drawend = () => {
        
        if (canvas){
            renderer.clear();
            if(game.winner === 'Server TimeOut')
            {
                updateText('Server TimeOut');
            }
            else
                updateText('Win ' + game.winner);
        }
    }

    const render = () => {
        if(canvas)
        {
            if(game.end)
            {
                Drawend();
                return ;
            }
            updateText(score);
            if(popupstore.game.gamestatus == 'play' && popupstore.game.team == 1)
            {
                player1Bar.position.set(10, (com.y), 10);
                player2Bar.position.set(GameTable.width - 10, (user.y), 10);
            }
            else{
                player1Bar.position.set(10, (user.y), 10);
                player2Bar.position.set(GameTable.width - 10, (com.y), 10);
            }
            gameBall.position.set(ball.x , ball.y, ball.radius);
        }
    }

    const aiPlaygame = () => {
        update();
        render();
    }

    const getMousePos = (event : MouseEvent) => {
        if (canvas)
        {
            let rect = canvas.getBoundingClientRect();
            user.y = -(event.clientY - rect.top - GameTable.height/4);
            if (user.y < -(GameTable.height))
                user.y = -(GameTable.height);
            else if(user.y > (0))
                user.y = (0);
            if(popupstore.game.gamestatus === 'play')
                popupstore.setServerY(-(user.y + user.height/2));
        }
    }

    const getScoreString = () => {
        score = '';
        if(popupstore.game.team === 1)
        {
            score += `${com.score}`;
            score += '  VS  ';
            score += `${user.score}`;
        }
        else{
            score += `${user.score}`;
            score += '  VS  ';
            score += `${com.score}`;
        }
    }

    const socketStore = useSocketStore();

    const popupstore = usePopupStore();

    const gameStat = computed(() => popupstore.getGameStatus);

    function updateText(newText :string) {
        updateCanvasText(newText);
        texture.needsUpdate = true; 
    }

    function initThree() {
        scene = new THREE.Scene();
        if(canvas)
        {
            camera = new THREE.PerspectiveCamera(75, canvas.width / canvas.height, 0.1, 1000);
            camera.position.z = 380;
            camera.position.y = -450;
            camera.position.x = 300;

            camera.castShadow = true;
            camera.lookAt(300, -200 ,0);
        } 
        if (canvas) {
            renderer = new THREE.WebGLRenderer({ canvas: canvas});
            renderer.setSize(canvas.width, canvas.height);
            getScoreString()
            updateCanvasText(score);
            const scoreMaterial = new THREE.MeshBasicMaterial({ map: texture });
            const scoreGeometry = new THREE.PlaneGeometry(500, 150);
            const scoremesh = new THREE.Mesh(scoreGeometry, scoreMaterial);
            scoremesh.position.set(300, 200 ,50);
            scoremesh.rotation.x = Math.PI / 4;
            scene.add(scoremesh);
            
            const material = new THREE.MeshBasicMaterial({ color: 'white' });
            const geometry = new THREE.BoxGeometry(20, 100, 20);
            const redmaterial = new THREE.MeshBasicMaterial({ color: 'red' });
            player1Bar = new THREE.Mesh(geometry, redmaterial);
            player1Bar.position.set(10 , -GameTable.height/2 , 10);
            scene.add(player1Bar);

            const bluematerial = new THREE.MeshBasicMaterial({ color: 'blue' });
            player2Bar = new THREE.Mesh(geometry, bluematerial);
            player2Bar.position.set(GameTable.width - 10, -GameTable.height/2 , 10);
            scene.add(player2Bar);

            const ballgeometry = new THREE.SphereGeometry(ball.radius, 20, 20);
            gameBall = new THREE.Mesh(ballgeometry, material);
            gameBall.position.set(ball.x, ball.y, ball.radius);
            scene.add(gameBall);

            const loader = new GLTFLoader();
            loader.load(
                '/pingpong.glb',
                (gltf) => {
                    gltf.scene.position.set(300, -200, 0);
                    gltf.scene.scale.set(2.2, 2.6, 2);

                    gltf.scene.traverse((child: THREE.Object3D) => {
                    if ((child as THREE.Mesh).isMesh) {
                        const mesh = child as THREE.Mesh;
                        if (Array.isArray(mesh.material)) {
                            mesh.material.forEach((mat) => {
                                if (mat instanceof THREE.MeshStandardMaterial) {
                                    mat.roughness = 0.8;
                                }
                            });
                        } else if (mesh.material instanceof THREE.MeshStandardMaterial) {
                            mesh.material.roughness = 1;
                        }}
                    });

                    scene.add(gltf.scene);
                },
                undefined,
                (error) => {
                    console.error('GLB loading error:', error);
                }
            );
            const tabegeometry = new THREE.BoxGeometry(1100 , 500, 1);

            const tabematerial = new THREE.MeshPhongMaterial({
                color: 0xffffff,
                emissive: 0xffffff, 
            });            
            table = new THREE.Mesh(tabegeometry, tabematerial);
            table.position.set(300, -50, -450);
            scene.add(table);

            const ambientLight = new THREE.AmbientLight(0xffffff, 8);
            scene.add(ambientLight);

            const directLight = new THREE.DirectionalLight(0xffffff, 5);
            directLight.position.set(0, 0 ,50);
            scene.add(directLight);
    }}

    const animate = () => {
        if(renderer)
        {
            animateID = requestAnimationFrame(animate);
            if(popupstore.game.gamestatus == 'ai')
                aiPlaygame();
            else if (popupstore.game.gamestatus == 'play')
                Playgame();
            renderer.render(scene, camera);
        }
    };


    const AiStartGame = () => {
        popupstore.setGameStatus('ai');
        socketStore.socketOffGameUpdate();
        socketStore.socketOffEndGame();
        socketStore.cancelGame(); 
        if (canvas) {
            game.end = false;
            game.winner = '';
            game.match = false;
            canvasresize();
            resetwindow(user, com);
            canvas.addEventListener("mousemove", getMousePos);
        }
        animate();
    }

    const canvasresize = () => {
            if (childDiv.value)
            {
                if(canvas){
                    canvas.width = childDiv.value.offsetWidth;
                    canvas.height = childDiv.value.offsetHeight;
                    emitHeight();
                    if(renderer && camera)
                    {
                        renderer.setSize(canvas.width, canvas.height);
                        camera.aspect = canvas.width / canvas.height;
                        camera.updateProjectionMatrix();
                    }
                }
            }
    }
//
    //새로고침시 이어서 게임할려면  이부분 바꿔야됨
    popupstore.setGameStatus('start');
    //  
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
        {
            if (animateID !== 0) {
                cancelAnimationFrame(animateID);
                animateID = 0;
            }
            renderer.clear();
        }
        popupstore.setGameStatus('start');
    }

    const updateObj = () => {
        if(canvas)
        {
            user.x = popupstore.game.me.x;
            user.score = popupstore.game.me.score;

            com.x = popupstore.game.you.x;
            com.y = -(popupstore.game.you.y + com.height/2);
            com.score = popupstore.game.you.score;

            ball.x = popupstore.game.ball.x;
            ball.y = -popupstore.game.ball.y;
        }
        getScoreString();
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
                animate();
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
//

    const cleanupThree = () => {
        if (animateID != 0) {
            cancelAnimationFrame(animateID);
            animateID = 0;
        }
        if(canvas)
            canvas.removeEventListener("mousemove", getMousePos);
        window.removeEventListener("resize", canvasresize);
        renderer.dispose();
    }
    onMounted(() => {

        if (canvasRef.value) 
        {
            canvas = canvasRef.value;
            emitHeight();
            canvas.width = canvasRef.value.offsetWidth;
            canvas.height = canvasRef.value.offsetHeight;
            initThree();
            window.addEventListener("resize", canvasresize);
        }
    });

    onUnmounted(() => {
        cleanupThree();
        if(intervalID != 0)
        {
            clearInterval(intervalID);
            intervalID = 0;
        }

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
    background-color: #9c9c9c;
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