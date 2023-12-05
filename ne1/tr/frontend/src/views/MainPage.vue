<template>
    <div class="main-page">
        <div class="navigator">
            <img src='/title.png' @click="homePage" class="title">
            <ProfileLayout />
            <div class="bottomdiv"></div>
        </div>
        <div class="content" :style="{ height: childHeight + 'px' }">
            <ThreeDPingPong v-if="gamemode == '3d'" @updateHeight="setHeight"/>
            <PingPong v-if="gamemode == '2d'" @updateHeight="setHeight"/>
            <ChatLayout/>
        </div>
    </div>
</template>

<script setup lang="ts">
import ProfileLayout from '@/components/profile/ProfileLayout.vue';
import PingPong from '@/components/game/PingPong.vue';
import ThreeDPingPong from '@/components/game/3dPingPong.vue';
import ChatLayout from '@/components/chat/ChatLayout.vue';
import { useUserStore } from '@/store/user';
import { usePopupStore } from '@/store/status'
import { useSocketStore } from '@/store/socket';
import { fetchData, apiClient } from '@/axios/api';
import {ref, onMounted, computed } from 'vue';
import router from '@/router';


const childHeight = ref<number>(0);

const userstore = useUserStore();

const popupstore = usePopupStore();

const gamemode = computed(() => popupstore.game.mode);

const homePage = () => {
    router.go(0);
}

function setHeight(height: number) {
  childHeight.value = height;
}

const socketStore = useSocketStore();

const socketinit = () => {
    socketStore.setsocket();
    socketStore.socketOnMsg();
    socketStore.socketOnNotification();
    socketStore.socketOnChangeAdmin();
    socketStore.socketOnFetchFriend();
    socketStore.restoreChannel();
}

interface UserData {
    id: number;
    username: string;
    avatar: string;
    twofactorauth : boolean;
    }

const data = ref<UserData | null>(null);


const setUser = (id : number) => {
        
    fetchData(id).then(res =>{

        data.value = res;
        if(data.value)
        {
            userstore.setUser({
            id: data.value.id,
            name: data.value.username,
            avatar: data.value.avatar,
            twofactorauth : data.value.twofactorauth
            })
        }
        socketinit();
        userstore.fetchBlocks();
        }).catch(error => {
            console.log("ERROR FETCH" + error);
        });
}

onMounted(() => {
    if(useUserStore().user.id === 0)
        router.replace('/');
    apiClient.defaults.headers.common['Authorization'] = `${useUserStore().user.token}`;
    setUser(useUserStore().user.id);
});

</script>

<style scoped>

.main-page {
    width: 100vw;
    height: 100vh;
    overflow: hidden;
    font-family: sansation_bold;
    background-color:#e6e7e8;
}

.navigator {
    position: relative;
    display: flex;
    flex-direction: row;
    width: 100%;
    height: 70px;
    background-color: #B61A1A;
    box-shadow: 2px 2px 2px 2px rgb(191, 191, 191);
    overflow: hidden;
}

.title {
    position: absolute;
    width: 220px;
    height: auto;
    top: -75px;
    font-weight: 700;
    font-size: 30px;
    color: white;
}

.title:hover {
    filter: brightness(0.4);
}

.bottomdiv {
    position: relative;
    width: 100%;
    height: 5px;
    background-color:white;
}
.content {
    position: relative;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    padding: 30px;
}

.testbox{
    position: absolute;
    display: flex;
    flex-direction: row;
    top : 70px;
    left : 30px;
    height: 30px;
    z-index: 999;
}

</style>
