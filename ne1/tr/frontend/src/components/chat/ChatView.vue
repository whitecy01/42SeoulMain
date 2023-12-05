<template>
  <img v-if="isSelect" src="/back.png" class="exit" @click="exitRoom">
  <div class="chatview">
    <ChatList v-if="!isSelect" @select="selectChannel"/>
    <div v-if="isSelect && selectCh">
      <ChatRoom :channel="selectCh" />
    </div>
  </div>
  <Msginput v-if="isSelect && selectCh" @sendMsg="sendMessage"/>
  <div class="boader-bottom"></div>
</template>
  
<script lang="ts" setup>
  import ChatList from './ChatList.vue';
  import ChatRoom from './ChatRoom.vue'
  import Msginput from './MsgInput.vue';
  import { watch, ref, computed } from 'vue';
  import { useUserStore, Channel } from '@/store/user';
  import { useSocketStore } from '@/store/socket';

  const emits = defineEmits(['chatname', 'exit']);

  const emitChannelName = (name : string) => {
   
    if(selectCh.value && selectCh.value.type === 'dm')
      emits('chatname', '(DM)' + name);
    else
      emits('chatname', name);
  }

  const userstore = useUserStore();

  const props = defineProps<{isExit : boolean}>();

  const isSelect = computed(()=> userstore.getChannelsList.findIndex(item => item.roomname === selectCh.value?.roomname) != -1)

  const selectCh = ref<Channel>();

  const socketStore = useSocketStore();


  watch(() => props.isExit,
    (isexit) => {
      if(isexit == true)
      {
        selectCh.value = undefined;
        emits('exit');
      }
  });

  watch(() => isSelect.value,
    (select) => {
      if(select == false)
      {
        selectCh.value = undefined;
        emits('exit');
      }
  });

  const sendMessage = (msg : string) => {
    if(selectCh.value)
    {
      const sendObj = {
        type : selectCh.value.type,
        roomname : selectCh.value.roomname,
        userid : userstore.user.id,
        msg : msg
      }
      socketStore.sendMessage(sendObj);
    }
  }
  
  const selectChannel = (channel : Channel) => {
      selectCh.value = channel;
      emitChannelName(channel.roomname);
  }

  const exitRoom = () => {
    selectCh.value = undefined;
    emitChannelName('PingPong Chat');
  }
  
</script>
  
  <style scoped>
    .chatview {
        position: relative;
        display: flex;
        left: 2.5%;
        width: 95%;
        height: 85%;
        font-size: 14px;
        background-color: whitesmoke;
        flex-direction: column;
        overflow-y:auto;

    }
    .boader-bottom {
        width: 100%;
        height: 5px;
        background-color: white;
    }


    .exit {
        position:absolute;
        right: 5px;
        top : 20px;
        width: 25px;
        height: 25px;
        z-index: 1;
      }

  </style>
  