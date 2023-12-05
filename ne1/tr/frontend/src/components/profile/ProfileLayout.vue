<template>
  <div class="popuplayout">
    <NameButton class="user-name" />
    <FriendPopup />
    <BlockListPopup />
    <NotificationBell />
    <SetPopup />
  </div>
</template>
  
  <script lang="ts" setup>
    import FriendPopup from './FriendPopup.vue';
    import BlockListPopup from './BlockListPopup.vue';
    import SetPopup from './SetProfilePopup.vue';
    import NameButton from './NameButton.vue';
    import NotificationBell from './NotificationBell.vue';
  
  </script>

  <style scoped>

  .popuplayout{
    position:absolute;
    display: flex;
    top: 18px;
    right: 0;
    flex-direction: row;
    justify-content: right;
    font-family: Helvetica;
    margin-right: 7px;
  }
  
  .user-name {
    width: auto;
    height: 35px;
    cursor: pointer;
    margin-right: 7px;

  }


  .homebutton {
    width: 50px;
    height: auto;
    border-radius: 50%;
  }
  </style>