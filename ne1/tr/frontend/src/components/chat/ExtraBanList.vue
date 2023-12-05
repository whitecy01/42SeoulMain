<template>
    <BasicActionList :isvisible = "visible" :mousePosition="position" @mouseleave="emitClose">
      <div @click="cancelBan()">Ban해제</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
  import { computed } from 'vue';
  import BasicActionList from '@/components/common/BasicActionList.vue';
  import { useUserStore, User } from '@/store/user';
  import { PostCancelBan } from '@/axios/api';
  
  interface Position {
    x : string,
    y : string,
  }

  interface Props {
    visible: boolean;
    position: Position;
    select : User;
    roomname : string;
  }
  
  const props = defineProps<Props>();
  const friend = computed(() => props.select);
  const emit = defineEmits(['mouseleave', 'cancel']);
  const emitClose = () => {
        emit('mouseleave');
  }
  const userstore = useUserStore();

  const cancelBan = async() => {
      try {
        const response = await PostCancelBan( props.roomname , friend.value.id, userstore.user.id);
        if (response.status === 200) {
          emit('cancel');
        }
      } catch {
        console.error('Error');
      }
      emitClose();
    };

  </script>
  