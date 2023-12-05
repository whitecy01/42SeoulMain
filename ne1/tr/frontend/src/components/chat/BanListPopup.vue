<template>
    <div class="banlist-button-icon">
        <BasicPopup :isOpen="popupOpen" @close="closePopup">
            <div class="ban-list-container" @scroll="handleScroll">
                <div v-for="friend in visibleFriends" :key="friend.id"  class="popup-content" @contextmenu.prevent="event => handleContextMenu(friend, event)">
                    <div :class="{'green-background': friend.status !== 'offline', 'red-background': friend.status === 'offline'}" class="status_circle"></div>
                    <span class="fr_status">{{ friend.status }}</span> 
                    <span class="fr_name">{{ friend.username }}</span>
                </div>
            </div>
        </BasicPopup>
        <ExtraBanList :visible="extraPopupVisible" :position="chatPosition" :select="selectFreind" :roomname="roomname" @mouseleave="closeChat" @cancel="reBanList"/>
    </div>
</template>

<script setup lang="ts">
import { ref, computed, watch } from 'vue';
import BasicPopup from '@/components/common/BasicPopup.vue';
import { usePopupStore } from '@/store/status';
import { useUserStore, User } from '@/store/user';
import { GetBanList }from '@/axios/api'
import ExtraBanList from './ExtraBanList.vue'

const banList = ref<User[]>([]);

const popupStore = usePopupStore();

const userstore = useUserStore();

const channel = computed(() => userstore.getChatRoom);

const roomname = computed(()=> {
    if(channel.value)
    {
        if (channel.value.roomname)
            return channel.value.roomname;
        else 
            return '';
    }
    return '';
})

const popupname  = 'Banlist';

const popupOpen = computed(()=> popupStore.popupname.includes(popupname));

watch(() => popupOpen.value,
        (check) =>  
        {
            if(check == true)
            {
                BanlistUpdate();
            }
        });

const visibleFriendCount = ref(8);

const hasMoreData = computed(() => visibleFriendCount.value < banList.value.length);

const visibleFriends = computed(() => banList.value.slice(0, visibleFriendCount.value));

const handleScroll = (event: Event) => {
  const container = event.target as HTMLElement;
  if (container.scrollTop + container.clientHeight >= container.scrollHeight && hasMoreData.value) {
    visibleFriendCount.value += 8;
  }
};

const extraPopupVisible = ref(false);

const chatPosition = ref({ x: '0px', y: '0px' });

const selectFreind = ref<User>({ id :0 , status :'', username :'', avatar:''});

const handleContextMenu = (friend: { id :number , status :string, username :string, avatar:string}, event: MouseEvent) => {
  chatPosition.value.x = `${event.pageX}px`;
  chatPosition.value.y = `${event.pageY}px`;
  extraPopupVisible.value = true;
  selectFreind.value = friend;
};

const BanlistUpdate = () => {
    if(channel.value)
    {
        GetBanList(roomname.value, userstore.user.id)
        .then( res => {
            banList.value = res;
        }
        ).catch( error =>{
            console.log('error GetBanList');}
        );
    }
}

const reBanList = () => {
    BanlistUpdate();
    closePopup();
}

const closeChat = () => {
  extraPopupVisible.value = false;
}

const closePopup = () => {
    popupStore.setPopup('');};
</script>

<style scoped>
    .banlist-button-icon {
        position: relative;
        display: flex;
        width: 26px;
        height: 26px;
    }
    .ban-list-container {
    margin-top: 10px;
    margin-bottom: 10px;
    height: 350px;
    text-align: left;
    overflow-y: auto;
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
    .fr_name {
    position: absolute;
    font-size: 14px;
    right:7%;
    }

    .popup-content:hover{
    background-color:#01B9BB;
    }
    .image-button{
        position: absolute;
        top: 50%;
        right: 0px;
        width: 26px;
        height: 26px;
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
</style>