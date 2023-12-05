<template>
    <div class="invite-button-icon">
        <img src="/invite.png" alt="x" class="image-button" @click="openFindWindow" />
        <BasicPopup :isOpen="popupOpen" @close="closePopup">
            <input v-model="newFriend" placeholder="User name" class="input-field" />
            <button @click="inviteFriend" class="friendadd_bt">Invite</button>
        </BasicPopup>
    </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';
import BasicPopup from '@/components/common/BasicPopup.vue';
import { usePopupStore } from '@/store/status';
import { useUserStore } from '@/store/user';
import { PostInviteUser }from '@/axios/api'


// const imageUrl = ref('/leave-button.svg');
const newFriend = ref<string>('');
const popupStore = usePopupStore();

const popupname  = 'IviteChannel';

const popupOpen = computed(()=> popupStore.popupname === popupname);

const userstore = useUserStore();

const channel = userstore.getChatRoom;

const inviteFriend = async() => {
    if (channel)
    {
        try {
            const response = await PostInviteUser(channel.roomname, newFriend.value);
            if (response.status === 200) {
                //
            }
        } catch {
                console.error('Error Invite');
        }
    }
    //addFriendDB(newFriend.value); 친구추가요청
    console.log(newFriend.value);
    newFriend.value = '';
}

const openFindWindow = () => {
    popupStore.setPopup(popupname);};

const closePopup = () => {
    popupStore.setPopup('');};
</script>

<style scoped>
.invite-button-icon {
    position: relative;
    display: flex;
    align-items: center;
    min-width: 26px;
    min-height: 26px;
    width: 20%;
}
.image-button{
    position: absolute;
    width: fit-content;
    top: 50%;
    right: -35%;
    transform: translate(-50%, -50%);
    max-width: 100%;
    max-height: auto;
}
.image-button:hover {
    filter: opacity( 0.2);
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
    height: auto;
}
</style>