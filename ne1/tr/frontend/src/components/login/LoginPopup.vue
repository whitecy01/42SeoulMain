<template>
    <div class="background">
    <div>
    <span v-for="(char, index) in animatedText" :key="index" :style="{ 'animationDelay': `${index * 0.1}s` }" class="welcome">{{ char }}</span>
    </div>
    <div class='login'>
        <img src="/table.png" class="table">
        <div class='title'>
        <h1>Login with&nbsp;</h1>
        <h1 class='ft'>42</h1>
        </div>
        <button class='login_button' @click=handleLogin()>
        <img src='/42.png' alt="42" />
        </button>
    </div>
</div>
</template>

<script lang="ts" setup>
    import { ref, watchEffect } from 'vue';

    const text = ref("PingPong");
    const animatedText = ref<string[]>([]);

    const handleLogin = () => {
        window.location.href = `${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/auth/42login`;
    }   

    watchEffect(() => {
        animatedText.value = text.value.split('');
    });
</script>

<style scoped>
    .background{
        position: absolute;
        display: flex;
        justify-content: center;
        width: 100%;
        height: 100%;
        background-color:#e6e7e8;
    }
    .login {
        position:fixed;
        display: flex;
        justify-content: center;
        top: 40%;
        left: 50%;
        transform: translate(-50%, 0%);
        width: 300px;
        height: 200px;
        text-align: center;
        border-color: white;
        background-color: #265196;
    }

    .title {
        position: absolute;
        top: 20px;
        display: flex;
        justify-content: center;
        align-items: center;
        color: white;
    }

    .ft {
        color: #01B9BB;
    }

    .login_button {
        position: absolute;
        background-color: #01B9BB;
        width: 50px;
        height: 50px;
        top: 120px;
        border-radius: 50%;
        border: #01B9BB;
    }

    .login_button:active {
        filter: brightness(1.8);
    }

    .login_button:hover {
        filter: brightness(1.2);
    }

    .login_button img {
        width: 35px;
        height: 35px;
    }
    
    .table {
        position: relative;
        width: 100%;
        height: auto;
    }
    .welcome {
        position: relative;
        top: 20%;
        font-family: sansation_bold;
        font-size: 100px;
        animation: bounce 2.4s infinite;
        display: inline-block;
        margin-right: 5px;
        color: #B61A1A;
    }

    @keyframes bounce {
        0%, 20%, 50%, 80%, 100% {
            transform: translateY(0);
        }
        40% {
            transform: translateY(-10px);
        }
        60% {
            transform: translateY(-5px);
        }
    }


</style>