<template>
  <div class="img-box">
    <div v-if="notificationNumber > 0" class="notiNumber">{{ notificationNumber }}</div>
    <img src="/bell.png" alt="Notion" @click="() => openPopup()" class="img-button" />
  </div>
  <transition name="slide-up-fade">
  <div v-if="isvisible && notificationNumber > 0" class="notifications">
    <NotItem v-for="(notification, index) in notifications"
      :key = "index"
      :type = "notification.type"
      :userid = "notification.userid"
      :name = "notification.username"
      :index="index"
    />
  </div>
  </transition>
</template>


<script lang="ts" setup>
  import { ref, computed } from 'vue';
  import { usePopupStore } from '@/store/status';
  import NotItem from './NotItem.vue';

  const popupStore = usePopupStore();
  
  const isvisible= ref<boolean>(false);

  const notificationNumber = computed(() => popupStore.getNotifications.length);

  const notifications = computed(() => popupStore.getNotifications);

  const openPopup = () => {
    if(!isvisible.value)
      isvisible.value = true;
    else
      isvisible.value = false;
  }

</script>

<style scoped>
  .img-box{
    position: relative;
  }
  .notiNumber {
    position: absolute;
    top: 0;
    right: 0;
    display: flex;
    justify-content: center;
    align-items: center;
    width: 20px;
    height: 20px;
    border-radius: 50%;
    font-size: 11px;
    background: rgba(255,255,0,1);
    color:black;
    font-weight: bolder;
  }
  .img-button {
    width: 35px;
    height: 35px;
    cursor: pointer;
    margin-right: 8px;
  }

  .img-box:hover{
    filter:brightness(0.2)
  }

  .notifications{
    position:fixed;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    top: 70px;
    right: 0;
    width: 300px;
    height: auto;
    overflow-y: auto;
    z-index: 999;
    border-style:solid;
    border-color: white;
    border-width: 2px;
    padding-bottom: 1px;
    max-height: 416px;
    background-color: rgba(88,88, 88, 0.8);
  }

    .slide-up-fade-enter-from, .slide-up-fade-leave-to {
    transform: translateY(-50%);
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
