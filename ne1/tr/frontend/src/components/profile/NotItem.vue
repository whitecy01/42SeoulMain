<template>
    <div class="addfriend">
        <img src="/close.png" class="close" @click="deleteItem">
        <div v-if="type === 'friend'">
        {{ name }} 에게 친구요청이 왔습니다
        <button @click="addFriend"> 수락 </button>
        </div>
        <div v-if="type === 'game'">
        {{ name }} 에게 게임요청이 왔습니다
        <button @click="addFriend"> 수락 </button>
        </div>
        <div v-if="type === 'not'">
        {{ name }}
        </div>
    </div>
</template>

<script setup lang="ts">
    import { useUserStore } from '@/store/user';
    import { usePopupStore } from '@/store/status';
    import { useSocketStore } from '@/store/socket';

    const props = defineProps<{
        type : 'friend' |'game' |'not',
        userid : number,
        name : string,
        index : number
    }>();

    const userstore = useUserStore();

    const popupstore = usePopupStore();

    const socketStore = useSocketStore();

    const deleteItem = () =>{
        popupstore.deleteNotification(props.index);
    }

    const addFriend = () => {
        socketStore.addFriend(userstore.user.id ,props.userid);
        popupstore.deleteNotification(props.index);
    }

</script>

<style scoped>
    .close {
        position: absolute;
        right: 10px;
        width: 10px;
        height: 10px;
    }

    .close:hover {
        filter:brightness(0.2);
    }
    .addfriend{
        display: flex;
        justify-content: center;
        align-items: center;
        width: 100%;
        height: 50px;
        min-height: 50px;
        font-size: 14px;
        border-bottom: 1px;
        border-color: aliceblue;
        border-width: 1px;
        border-style: outset;
        background-color: rgba(222,222,222,0.7);
    }
</style>