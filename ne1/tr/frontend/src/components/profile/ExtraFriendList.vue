<template>
    <BasicActionList :isvisible = "visible" :mousePosition="position" @mouseleave="emitClose">
      <div class="list-box" @click="showProfile()">프로필보기</div>
      <div class="list-box" v-if="select.status !== 'OFFLINE'" @click="connectchat()">채팅하기</div>
      <div class="list-box" @click="deletefriend()">친구삭제</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
  import { computed } from 'vue';
  import BasicActionList from '@/components/common/BasicActionList.vue';
  import { useUserStore, User } from '@/store/user';
  import { useSocketStore } from '@/store/socket';
  import { PostDeleteFreind } from '@/axios/api';
  import { usePopupStore } from '@/store/status';
  
  interface Position {
    x : string,
    y : string,
  }

  interface Props {
    visible: boolean;
    position: Position;
    select : User;
  }
  const props = defineProps<Props>();
  const friend = computed(() => props.select);
  const emit = defineEmits(['mouseleave']);
  const emitClose = () => {
        emit('mouseleave');
  }
  const userstore = useUserStore();

  const socketStore = useSocketStore();

  const connectchat = async () => {
    const index = userstore.user.Channels.findIndex(item => item.roomname == (friend.value.username + ' |'))
    if (index == -1)
      socketStore.enterRoom('dm', friend.value.username);
    emitClose();
  };

  const showProfile = () => {
    console.log(friend);
    usePopupStore().setSelectFriend(friend.value.intraId);
    usePopupStore().setSelectFriendName(friend.value.username);
    usePopupStore().setSelectAvatar(friend.value.avatar);
    usePopupStore().setSelectName(friend.value.username);
    usePopupStore().setPopup('FriendProfile');
    emitClose();
  };

  const deletefriend = async() => {
      try {
        const response = await PostDeleteFreind(userstore.user.id, friend.value.id);
        if (response.status === 200) {
          userstore.fetchFriends();
          userstore.deleteDMChannel(friend.value.username);
        }
      } catch {
        console.error('Error');
      }
      emitClose();
    };

  </script>

  <style scoped>
  .list-box {
    display: flex;
    justify-content: center;
    align-items: center;
  }
  </style>
  