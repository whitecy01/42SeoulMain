<template>
  <img src="/block.png" alt="Friends" @click="() => openPopup()" class="img-button" />
  <BasicPopup :isOpen="popupOpen" @close="closePopup">
    <div class="friend-list-container" @scroll="handleScroll">
      <div v-for="friend in visibleFriends" :key="friend.id"  class="popup-content" @contextmenu.prevent="event => handleContextMenu(friend, event)">
        <span class="fr_name">{{ friend.username }}</span>
      </div>
    </div>
    <transition name="slide-up-fade">
    <div v-if="handleMsg" :class="{'success': handleMsg === 'success', 'error': handleMsg !== 'success' }">{{ handleMsg }}</div>
   </transition>
    <input v-model="newFriend" placeholder="유저이름을 입력해주세요" class="input-field"/>
    <button @click="addBlock" class="friendadd_bt">차단하기</button>
  </BasicPopup>
  <ExtraBlockList :visible="extraPopupVisible" :position="chatPosition" :select="selectFreind" @mouseleave="closeChat" />
</template>

<script lang="ts" setup>
  import { ref , computed } from 'vue';
  import BasicPopup from '@/components/common/BasicPopup.vue';
  import ExtraBlockList from './ExtraBlockList.vue';
  import { usePopupStore } from '@/store/status';
  import { useUserStore, User } from '@/store/user';
  import { PostaddBlock } from '@/axios/api';

  const newFriend = ref<string>('');

  const userstore = useUserStore();

  const friendslist = computed(() => userstore.getBlocks);

  const visibleFriendCount = ref(8);

  const hasMoreData = computed(() => visibleFriendCount.value < friendslist.value.length);

  const visibleFriends = computed(() => friendslist.value.slice(0, visibleFriendCount.value));

  const handleScroll = (event: Event) => {
    const container = event.target as HTMLElement;
    if (container.scrollTop + container.clientHeight >= container.scrollHeight && hasMoreData.value) {
      visibleFriendCount.value += 8;
    }
  };

  const popupStore = usePopupStore();

  const popupname  = 'BlockList';

  const popupOpen = computed(()=> popupStore.popupname === popupname);

  const handleMsg = ref('');

  const openPopup = () => {
    userstore.fetchBlocks();
    popupStore.setPopup(popupname);
  }

  const addBlock = () => {
    PostaddBlock(userstore.user.id , newFriend.value)
    .then(res => {
      if(res.status === 200)
      {
        handleMsg.value = 'success';
        userstore.fetchBlocks();
      }
      else
      {
        handleMsg.value = '차단 실패';
      }
      setTimeout(() => {
      handleMsg.value = '';
    }, 5000);  }).catch(error => {
      handleMsg.value = '차단 실패';
      setTimeout(() => {
      handleMsg.value = '';
      }, 5000);
      console.log('addblock 실패')});
  }

  const closePopup = () => {
    extraPopupVisible.value = false;
    popupStore.setPopup('');
  }

  const extraPopupVisible = ref(false);

  const chatPosition = ref({ x: '0px', y: '0px' });

  const selectFreind = ref<User>({ id :0 , status :'', username :'', avatar:''});

  const handleContextMenu = (friend: { id :number , status :string, username :string, avatar:string}, event: MouseEvent) => {
    chatPosition.value.x = `${event.pageX}px`;
    chatPosition.value.y = `${event.pageY}px`;
    extraPopupVisible.value = true;
    selectFreind.value = friend;
  };

  const closeChat = () => {
    extraPopupVisible.value = false;
  }

</script>

<style scoped>
.friend-list-container {
  margin-top: 10px;
  margin-bottom: 10px;
  height: 350px;
  text-align: left;
  overflow-y: auto;
}
.img-button {
    width: 33px;
    height: 33px;
    cursor: pointer;
    margin-right: 7px;
  }
  .img-button:hover{
    filter:brightness(0.2)
  }
.popup-content {
  display: flex;
  align-items: center;
  background: rgba(255,255,255,1);
  padding: 10px;
  margin: 5px;
  height: 18px;
  border-radius: 8px;
  width: auto;
}
.green-background {
    background-color: green;
}
.red-background {
    background-color: red;
}
.status_circle {
  width: 6px;
  height: 6px;
  border-radius: 50%;
}
.fr_status {
  position: absolute;
  font-size: small;
  left:7%;
}

.fr_name {
  position: absolute;
  font-size: 14px;
  right:7%;
}

.popup-content:hover{
  background-color:#01B9BB;
}

.input-field {
  margin-left: auto;
  margin-right: auto;
  width: 70%;
}

.friendadd_bt {
  margin-left: 12px;
  margin-right: auto;
  width: 23%;
  background-color:#20427A;
  border-radius: 2px;
  border: solid white 1.5px;
  color: white;
  height: auto;
}

.friendadd_bt:hover{
  filter: brightness(0.7);
}

.add-friend {
  display: flex;
  gap: 10px;
  margin-top: 15px;
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
