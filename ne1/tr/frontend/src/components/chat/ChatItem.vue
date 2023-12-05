<template>
    <div @contextmenu.prevent="$emit('contextmenu', $event)">
        <div v-if="type === 'message'" :class="{'My-chat-item': name === myName, 'chat-item': name !== myName }">
            <div class="profile" v-if="name !== myName ">
                <img :src="userAvtUrl" alt="User Avatar" class="avatar"/>
                <div class="username">{{ name }}</div>
            </div>
            <div class="message-content">
                {{ message }}
            </div>
        </div>
        <div v-if="type ==='notification'" class="notification">
            <div class="not-content">{{ message }}</div>
        </div>
    </div>
</template>
  
<script setup lang="ts">
    import {ref, inject} from 'vue'
    import { useUserStore, Msg } from '@/store/user';

    const props = defineProps<Msg>();

    const userstore = useUserStore();

    const imgPrefix = inject('imgUrlPrefix');

    const userAvtUrl = ref(imgPrefix + props.avatar);

    const myName = userstore.user.name;

</script>
  
<style scoped>
    .My-chat-item {
        display: flex;
        flex-direction: column;
        padding-top: 10px;
        align-items: last baseline;
    }
    .chat-item {
        display: flex;
        flex-direction: column;
        padding-top: 8px;
    }
    .profile {
        display: flex;
        flex-direction: row;
    }

    .username {
        display: flex;
        align-items: center;
    }
    .avatar {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        margin-right: 10px;
        background-color: blueviolet;
    }

    .message-content {
        position: relative;
        background-color: white;
        top: 6px;
        width: max-content;
        padding: 5px;
        border-radius: 8px;
        
    }
    .My-chat-item .message-content {
        background-color: yellow;
        
    }
    .notification {
        display: flex;
        justify-content: center;
        align-items: center;
        width: 100%;
        height: 20px;
        background-color: gainsboro;
        border-radius: 4px;
        margin-top: 9px;
    }

    .not-content {
        color: black;
        font-size: 10px;
    }
</style>
  