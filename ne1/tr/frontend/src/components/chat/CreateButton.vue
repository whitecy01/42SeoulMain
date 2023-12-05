<template>
    <div class="create-button-icon">
        <img src="/createroom.png" alt="x" class="image" @click="openImagePicker"/>
        <BasicPopup :isOpen="popupOpen" @close="closePopup">
            <div class="create-window">
                <div class="label">
                    <label>
                        <input type="radio" v-model="privateRoom" value="true" />
                        Private
                    </label>
                    <label>
                        <input type="radio" v-model="privateRoom" value="false" />
                        Public
                    </label>
                </div>
                <div class="status-box">
                    <transition name="slide-up-fade">
                        <div v-if="handleMsg" :class="{'success': handleMsg === 'success', 'error': handleMsg !== 'success' }">{{ handleMsg }}</div>
                    </transition>
                </div>
                <form class="fromcss">
                <div class="name-input">
                    <input v-model="roomName" autocomplete="off" placeholder="Room Name" />
                </div>
                    <div class="password-input">
                        <input 
                            v-model="password" 
                            type="password" 
                            placeholder="Password"
                            autocomplete="new-password" 
                            :class="{'gray-out' : !isPrivate}"
                            :readonly="!isPrivate"/>
                    </div>
                </form>
                <button class="create-button" @click="createRoom">Create</button>
            </div>
        </BasicPopup>
    </div>
</template>
  
<script setup lang="ts">
    import { ref, computed } from 'vue';
    import BasicPopup from '@/components/common/BasicPopup.vue';
    import { usePopupStore } from '@/store/status';
    import { useUserStore } from '@/store/user';
    import { useSocketStore } from '@/store/socket';
    import { PostCreateChannel } from '@/axios/api'

    const userstore = useUserStore();

    const privateRoom = ref('false');

    let roomName = ref('');

    let password = ref('');

    const isPrivate = computed(() => {
        return privateRoom.value === "true";
    });

    const popupStore = usePopupStore();

    const popupname  = 'CreateChannel';

    const popupOpen = computed(()=> popupStore.popupname === popupname);

    const socketStore = useSocketStore();

    const handleMsg = ref('');

    const openImagePicker = () => {
        popupStore.setPopup(popupname);
    };

    const closePopup = () => {
        popupStore.setPopup('');
    };

    const createRoom = async () => {
      try {
        if (privateRoom.value === 'false')
            password.value = '';
        if(userstore.user.Channels.findIndex(item => item.type === 'msg') != -1)
        {
            console.log('방만들기 전 기존 방 exit');
            socketStore.exitRoom();
        }
        const response = await PostCreateChannel(userstore.user.id, roomName.value, password.value, isPrivate.value );
        if (response.status === 200) {
            handleMsg.value = 'success';
            setTimeout(() => {handleMsg.value = '';}, 5000);
            socketStore.enterRoom('msg', roomName.value);
        }
        else
        {
            handleMsg.value = '방을 만들 수 없습니다.';
            setTimeout(() => {handleMsg.value = '';}, 5000);
        }
        popupStore.setPopup('');
      } catch {
            handleMsg.value = '방을 만들 수 없습니다.';
            setTimeout(() => {handleMsg.value = '';}, 5000);
      }
    }

</script>

<style scoped>
.create-button-icon {
    position: relative;
    display: flex;
    align-items: center;
    min-width: 23px;
    min-height: 23px;
    width: 16%;
}
.create-window {
    position: relative;
    display: flex;
    justify-content: center;
    width: 100%;
    height: 200px;
    overflow: hidden;
    text-align: center;
}

.label {
    position: relative;
    display: flex;
    flex-direction: row;
    top:20px;
}
.image {
    position: absolute;
    top: 50%;
    left: 50%;
    width: 100%;
    max-height: 140%;
    transform: translate(-50%, -50%);
    max-width: 100%;
}
.image:hover {
    filter: opacity( 0.2);
}

.status-box {
    position: absolute;
    top: 50px;
    width: 300px;
    height: 15px;
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
.fromcss{
    position: absolute;
    top: 70px;
    width: 300px;
}
.name-input {
    position: absolute;
    top: 0px;
    width: 300px;
    height: 30px;
}

.password-input {
    position: absolute;
    top: 40px;
    width: 300px;
    height: 30px;
}

.create-button {
    position: absolute;
    top: 150px;
    width: 100px;
    height: 20px;
    background-color: #20427A;
    border-radius: 5px;
    margin-top: 10px;
    color: white;
    justify-content: center;
  }

  .gray-out {
  background-color: gray;
  color: #888;
}
</style>