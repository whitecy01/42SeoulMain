<template>
    <BasicActionList :isvisible = "visible" :mousePosition="position" >
        <div class="list-box" @click="openDashPopup">DashBoard</div>
        <div class="list-box" @click="logOutUser">LogOut</div>
    </BasicActionList>
  </template>
  
  <script setup lang="ts">
    import BasicActionList from '@/components/common/BasicActionList.vue';
    import { usePopupStore } from '@/store/status';
    import { useUserStore } from '@/store/user';
    import { useSocketStore } from '@/store/socket';
    import router from '@/router';
    import { GetlogOut } from '@/axios/api';

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
    const socketstoe = useSocketStore();
    const popupStore = usePopupStore();
    const popupname = 'DashBoard';

    const openDashPopup = () => {
        popupStore.setPopup(popupname);
    }

    const logOutUser = () => {
        GetlogOut(userstore.user.id).then(res => {
            if(res)
            {
                userstore.resetStore();
                socketstoe.socketReset();
                popupStore.resetStore();
                router.replace('/');
            }
        }).catch(() => console.log('logout error'));
    }

  </script>

  <style scoped>
      .list-box {
    display: flex;
    justify-content: center;
    align-items: center;
  }
    </style>