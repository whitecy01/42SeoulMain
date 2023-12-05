<template>
  <div class="board">
      <img :src="userAvtUrl" alt="avatar" class="avatar-image" @click="openExtraList"/>
      <div @click="openExtraList" class="name-button">
          {{ user.name }}
      </div>
      <ExtraProfileList :visible="extraPopupVisible" :position="chatPosition" @mouseleave="closeChat"/>
      <DashBoard v-if="isDashBoard" @close="closePopup"/>
      <FriendProfile v-if="isFriendProfile" @close="closePopup"/>
  </div>
</template>

<script setup lang="ts">
import { ref, inject, computed } from 'vue';
import ExtraProfileList from '@/components/profile/ExtraProfileList.vue'
import DashBoard from './DashBoard.vue';
import FriendProfile from './FriendProfile.vue';
import { useUserStore } from '@/store/user';
import { usePopupStore } from '@/store/status';

const userStore = useUserStore();
const user = computed(() => userStore.user)

const imgPrefix = inject('imgUrlPrefix');

const userAvtUrl = computed(() => {
    if (user.value.avatar && user.value.avatar !== "") {
        return imgPrefix + user.value.avatar;
    }
    return "";});

const isFriendProfile = computed(() => (usePopupStore().popupname == 'FriendProfile' && usePopupStore().selectFriend != 0))

const isDashBoard = computed(() => (usePopupStore().popupname == 'DashBoard'))

const extraPopupVisible = ref(false);
const chatPosition = ref({ x: '0px', y: '0px' });

const openExtraList = (event: MouseEvent) => {
  chatPosition.value.x = `${event.pageX}px`;
  chatPosition.value.y = `${event.pageY}px`;
  extraPopupVisible.value = true;
};

const closeChat = () => {
  extraPopupVisible.value = false;
}

const closePopup = () => {
  usePopupStore().setPopup('');
  usePopupStore().setSelectName('');
  usePopupStore().setSelectAvatar('');
  usePopupStore().setSelectFriend(0);  
  usePopupStore().setSelectFriendName('');

}

</script>

<style scoped>
.board {
  display: flex;
  flex-direction: row;
}

.avatar-image {
  width: 35px;
  height: 35px;
  cursor: pointer;
  margin-right: 7px;
  max-height: auto;
  border-radius: 50%;
}

.name-button {
  width: auto;
  height: auto;
  font-size: 20px;
  margin-top: 5px;
  margin-right: 10px;
  color: white;
}

.content-list {
  max-height: 100px;
  overflow-y: auto;
  border: 1px solid #ccc;
  padding: 10px;
}

.content-item {
  margin-bottom: 10px;
}

.blue-text {
  color: blue;
}

.red-text {
  color: red;
}

.achievement-list {
  max-height: 100px;
  overflow-y: auto;
  border: 1px solid #ccc;
  padding: 10px;
}

.achievement-item {
  color: green;
  font-weight: bold;
}
</style>