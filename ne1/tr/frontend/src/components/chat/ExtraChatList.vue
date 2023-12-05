<template>
    <BasicActionList :isvisible="visible" :mousePosition="position" @mouseleave="emitClose">
      <div class="list-box" @click="showFrindProfile">프로필보기</div>
      <div class="list-box" v-if="(isAdimin || isOwner) && !isSelectOwner && !isSelectAdmin && isMember" @click="muteUser">채팅금지</div>
      <div class="list-box" v-if="isOwner  && isMember" @click="delegateAdmin">관리자위임</div>
      <div class="list-box" v-if="(isAdimin || isOwner) && !isSelectOwner  && !isSelectAdmin && isMember" @click="expelUser">추방하기</div>
      <div class="list-box" v-if="(isAdimin || isOwner) && !isSelectOwner  && !isSelectAdmin && isMember" @click="banUser">Ban하기</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
  import { computed } from 'vue';
  import BasicActionList from '@/components/common/BasicActionList.vue';
  import { useUserStore, Msg, Channel } from '@/store/user';
  import { usePopupStore } from '@/store/status';
  import { useSocketStore } from '@/store/socket'
  import { PostMuteUser } from '@/axios/api';
  
  interface Position {
    x : string,
    y : string,
  }

  interface Props {
    visible: boolean;
    position: Position;
    select : Msg;
    channel : Channel
  }

  const props = defineProps<Props>();

  const emit = defineEmits(['mouseleave']);
  
  const select = computed(() => props.select);

  const userstore = useUserStore();

  const socketstore = useSocketStore();

  const myName = userstore.user.name;

  const isAdimin = computed(()=> (props.channel.admin?.findIndex(item => item === myName)) != -1);

  const isOwner = computed(()=> props.channel.owner === myName);

  const isSelectOwner = computed(()=> props.channel.owner === props.select.name);

  const isSelectAdmin = computed(()=> (props.channel.admin?.findIndex(item => item === props.select.name)) != -1);

  const isMember = computed(() => props.channel.member?.findIndex(item => item.username === props.select.name) != -1);

  const muteUser =  async () => {
    try {
      const response = await PostMuteUser(select.value.id, select.value.name, props.channel.roomname, userstore.user.id);
      if (response.status === 200) {
        userstore.updateChat({type : 'not',roomname: props.channel.roomname, userid: userstore.user.id, username : userstore.user.name, expel : false, avatar: userstore.user.avatar, msg: `${select.value.name}님이 채팅금지 되었습니다.`})
      }
    } catch {
      console.error('Error Mute');
    }
    emitClose();
  };

  const emitClose = () => {
        emit('mouseleave');
  }

  const showFrindProfile = () => {
    usePopupStore().setSelectFriend(select.value.id);
    usePopupStore().setSelectName(select.value.name);
    usePopupStore().setSelectAvatar(select.value.avatar);
    usePopupStore().setSelectFriendName(select.value.name);
    usePopupStore().setPopup('FriendProfile');
    emitClose();
  }
  
  const expelUser = () => {
    socketstore.expelUser('expel' ,select.value.id, props.channel.roomname);
    emitClose();
  }

  const banUser = () => {
    socketstore.expelUser('ban' ,select.value.id, props.channel.roomname);
    emitClose();
  }

  const delegateAdmin = async () => {
    socketstore.delegateAdmin(props.channel.roomname ,select.value.id);
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