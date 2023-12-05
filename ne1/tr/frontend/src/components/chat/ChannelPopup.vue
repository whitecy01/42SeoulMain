<template>
    <div v-if="isOpen" class="popup">
      <div class="popupheader">
        <div class="popupname">{{ select.name }}</div>              
        <img src="/close.png" alt="Close" class="close-btn" @click="closePopup" />
        <div class="header_bottom"></div>
      </div>
      <div class="content">
        <div class="status-box">
          <transition name="slide-up-fade">
              <div v-if="handleMsg" :class="{'success': handleMsg === 'success', 'error': handleMsg !== 'success' }">{{ handleMsg }}</div>
          </transition>
        </div>
        <div v-if="select.status === 'private'" class="passwordBox">Password:
          <input class="password" placeholder="Enter password" v-model="password">
        </div>
        <button class="join-bt" @click="joinChannel">Join</button>
      </div>
    </div>
  </template>
  
  <script lang="ts" setup>  
    import {ref, computed } from 'vue';
    import { useSocketStore } from '@/store/socket';
    import {PostJoinChannel} from '@/axios/api';
    import { useUserStore } from '@/store/user';

    const props = defineProps<{ isOpen: boolean, select:{ name: string ,status: 'public' | 'private'} }>();
    
    const emits = defineEmits(['close']);

    const channel = computed(() => props.select);
    
    const password = ref<string>('');
     
    const socketStore = useSocketStore();
    
    const handleMsg = ref('');

    const closePopup = () => {
      emits('close');
    }

    const joinChannel = async () => {
      PostJoinChannel(useUserStore().user.id, channel.value.name, password.value).then(res =>{
        if(res.status == 200)
        {
          password.value = '';
          socketStore.enterRoom('msg', channel.value.name);
          closePopup();
        }
        else{
          handleMsg.value = '방에 들어가지 못했습니다.';
          password.value = '';
          setTimeout(() => {handleMsg.value = '';}, 5000);
        }
      }).catch(() =>
      { 
          console.log('channel Join Error')
          handleMsg.value = '방에 들어가지 못했습니다.';
          password.value = '';
          setTimeout(() => {handleMsg.value = '';}, 5000);
      });
    }
  </script>
  
  <style scoped>
  .popup {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    width:200px;
    padding: 20px;
    background-color: rgba(245, 245, 245, 0.8);
    border: 1px solid #ddd;
    z-index: 888;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5);
  
  }
  
  .popupheader {
    display: flex;
    position:absolute;
    top: 0%;
    left: 0%;
    width: 100%;
    height: 35px;
    background-color: #20427A;
  }

  .popupname {
  position: absolute;
  top: 5px;
  left: 10px;
  font-family: sansation_bold;
  color: white;
}

  
  .content {
    position: relative;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    top: 20px;
    padding: 5px;
    padding-bottom: 10px;
  }

  .passwordBox {
    display: flex;
    flex-direction: row;
  }

  .password {
    margin-left: 5px;
  }
  
  .join-bt {
    width: 100px;
    height: 20px;
    background-color: #20427A;
    border-radius: 5px;
    margin-top: 10px;
    color: white;
    justify-content: center;
  }
  
  .header_bottom {
    position: absolute;
    width: 100%;
    height: 4px;
    bottom: 0;
    background-color: white;
  }
  .close-btn {
    position: absolute;  
    top: 10px;          
    right: 10px;        
    cursor: pointer;
    width: 14px;
    height: 14px;
  }

  .status-box {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 100%;
    height: 15px;
    margin-bottom: 5px;
}

.success {
  display: flex;
  justify-content: center;
  color: green;
  z-index: 1;
  font-size: 12px;
}

.error {
  display: flex;
  justify-content: center;
  color: red;
  z-index: 1;
  font-size: 12px;
}

.slide-up-fade-enter-from, .slide-up-fade-leave-to {
  transform: translateY(100%);
  opacity: 0;
}

.slide-up-fade-enter-to, .slide-up-fade-leave-from {
  transform: translateY(0);
  opacity: 1;
}

.slide-up-fade-enter-active, .slide-up-fade-leave-active {
  transition: transform 0.5s ease-in-out, opacity 0.5s ease-in-out;
}

  </style>
  