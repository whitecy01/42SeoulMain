<template>
    <BasicActionList :isvisible="visible" :mousePosition="position" @mouseleave="emitClose">
      <div class="listbt" @click="activeChangePW">ChangePW</div>
      <div class="listbt" @click="activeBanList">BanList</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
    import { ref } from 'vue';
    import BasicActionList from '@/components/common/BasicActionList.vue';
    import { usePopupStore } from '@/store/status';
    import { useUserStore } from '@/store/user';
  
    interface Position {
        x : string,
        y : string,
    }

    interface Props {
        visible: boolean;
        position: Position;
    }

   defineProps<Props>();

    const userstore = useUserStore();

    const popupstore = usePopupStore();

    const channel = userstore.getChatRoom;

    const roomname = ref<string>('');

    if(channel)
        roomname.value =channel.roomname;

    const banPopupName  = 'Banlist (' + channel?.roomname + ')';

    const emit = defineEmits(['mouseleave']);

    const emitClose = () => {
            emit('mouseleave');
    }

    const activeChangePW =   () => {
        popupstore.setPopup('Change Password');
        emitClose();
    };

    const activeBanList =   () => {
        popupstore.setPopup(banPopupName);
        emitClose();
    };

  </script>

  <style scoped>
.listbt {
    font-size: 16px;
}
    </style>
  