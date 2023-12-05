<template>
    <BasicPopup :isOpen="popupOpen" @close="closePopup">
        <div class="channelName">RoomName : {{ channelName }}</div>
        <input v-model="newPassword" placeholder="New Password" class="input-field" />
        <button @click="ChangePW" class="change_bt">변경하기</button>
    </BasicPopup>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';
import BasicPopup from '@/components/common/BasicPopup.vue';
import { usePopupStore } from '@/store/status';
import { useUserStore } from '@/store/user';
import { PostChangePassword }from '@/axios/api'


const newPassword = ref<string>('');

const popupStore = usePopupStore();

const popupname  = 'Change Password';

const popupOpen = computed(()=> popupStore.popupname === popupname);

const userstore = useUserStore();

const channelName = computed(() => userstore.getChatRoom?.roomname);

const ChangePW = async() => {
    if (channelName.value)
    {
        try {
            const response = await PostChangePassword(channelName.value, newPassword.value, userstore.user.id);
            if (response?.status === 200) {
                closePopup();
            }
        } catch {
                console.error('Error Invite');
        }
    }
    newPassword.value = '';
}

const closePopup = () => {
    popupStore.setPopup('');};
</script>

<style scoped>
.channelName{
    width: 100%;
    height: 30px;
}
.input-field {
    margin-left: auto;
    margin-right: auto;
    width: 70%;
}

.change_bt {
    margin-left: 12px;
    margin-right: auto;
    width: 23%;
    height: auto;
}
</style>