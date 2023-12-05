<template>
    <BasicActionList :isvisible = "visible" :mousePosition="position" @mouseleave="emitClose">
      <div class="list-box" @click="deleteblock()">차단해제</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
  import { computed } from 'vue';
  import BasicActionList from '@/components/common/BasicActionList.vue';
  import { useUserStore, User } from '@/store/user';
  import { PostDeleteBlock } from '@/axios/api';
  
  interface Position {
    x : string,
    y : string,
  }

  interface Props {
    visible: boolean;
    position: Position;
    select : User;
  }
  const props = defineProps<Props>();
  const friend = computed(() => props.select);
  const emit = defineEmits(['mouseleave']);
  const emitClose = () => {
        emit('mouseleave');
  }
  const userstore = useUserStore();

  const deleteblock= async() => {
      try {
        const response = await PostDeleteBlock(userstore.user.id, friend.value.id);
        if (response.status === 200) {
          userstore.fetchBlocks();
        }
      } catch {
        console.error('Error');
      }
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
  