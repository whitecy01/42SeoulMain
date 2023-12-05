    <template>
        <div class="Chatlayout">
            <div class="Roomname">
                <div class="roomname_top"></div>
                <div class="roomname_content">
                    <div class="roomname">{{ channelName }}</div>
                    <img src="/manager.png" v-if="isAdimin && isChannel" alt="x" class="image-button" @click="handleContextMenu" />
                </div>
                <ExtraManager v-if="extraPopupVisible" 
                    :visible="extraPopupVisible"         
                    :position="chatPosition" 
                    @mouseleave="closeChat"/>
            </div>
                <Chatview @chatname="setChannelname" @exit="checkexit" :isExit="isexit"/>
            <div class="chatbuttonBox">
                <div class="chatbuttons-left">
                    <ChannelFindButton/>
                    <CreateButton/>
                </div>
                <div class="chatbuttons-right">
                    <img class="leave-button-icon" alt="" src="/exit.png" @click="exitRoom"/>
                </div>
            </div>
        </div>
        <BanListPopup/>
        <ChangePassword/>
    </template>
  
    <script setup lang="ts">
        import Chatview from './ChatView.vue';
        import CreateButton from './CreateButton.vue';
        import ChannelFindButton from './ChannelFindButton.vue';
        import BanListPopup from './BanListPopup.vue';
        import ChangePassword from './ChangePassword.vue'
        import ExtraManager from './ExtraManager.vue';
        import { computed, ref } from 'vue'
        import { useSocketStore } from '@/store/socket';
        import { useUserStore } from '@/store/user';

        const socketStore = useSocketStore();

        const userstore = useUserStore();

        const channelName = ref<string>('PingPong Chat');

        const isexit = ref<boolean>(false);

        const isAdimin = computed(() => userstore.getChatRoom?.owner === userstore.user.name);
        
        const isChannel = ref<boolean>(false);

        const chatPosition = ref({ x: '0px', y: '0px' });

        const extraPopupVisible = ref(false);

        const exitRoom = () => {
            socketStore.exitRoom();
            isexit.value = true;
            channelName.value = 'PingPong Chat';
            isChannel.value = false;       
        }

        const checkexit = () => {
            isexit.value = false;
            channelName.value = 'PingPong Chat';
            isChannel.value = false;       
        }

        const setChannelname = ( name : string) => {
            if (name.length > 10) {
                channelName.value = name.substring(0, 10) + '...';
            }
            else
                channelName.value = name;
            if (name != 'PingPong Chat' && !name.includes('(DM)'))
                isChannel.value = true;
            else
                isChannel.value = false;       
        }

        const handleContextMenu = (event: MouseEvent) => {
                chatPosition.value.x = `${event.pageX}px`;
                chatPosition.value.y = `${event.pageY}px`;
                extraPopupVisible.value = true;
        };

        const closeChat = () => {
            extraPopupVisible.value = false;
        }
    </script>

    <style scoped>
    .Chatlayout{
        position:relative;
        display: flex;
        flex-direction: column;
        background-color: whitesmoke;
        width: 30vw;
        height: 100%;
        text-align: left;
        left: 30px;
        box-shadow: 2px 2px 2px 2px rgb(191, 191, 191);

    }
    .Roomname {
        display: flex;
        height: 50px;
        align-items: center;
        font-size: 25px;
        background-color: white;
        flex-direction: column;
    }

    .roomname_top {
        background-color: #265196;
        width: 100%;
        height: 15px;
    }

    .roomname_content {
        display: flex;;
        background-color:#3c3c3c;
        width: 100%;
        height: 100%;
        margin-top: 5px;
        align-items: center;
        color: white;
    }

    .roomname {
        max-width: 85%;
        padding-left: 15px;
        font-size:95%
    }

    .chatbuttonBox{
        position:relative;
        display: flex;
        align-items: center;
        flex: 1;
        width: 100%;
        background-color: #3c3c3c;
        padding-top: 5px;
        padding-bottom: 5px;
        flex-direction: row; 
    }
    .chatbuttons-left{
        display: flex;
        width: 50%;
        height: 70%;
        margin-left: 7px;
    }
    .chatbuttons-right{
        display: flex;
        width: 50%;
        margin-right: 7px;
        justify-content: right;
    }
    .leave-button-icon {
        position: relative;
        display: flex;
        align-items: center;
        min-width: 23px;
        min-height: 23px;
        width: 16%;
    }
    .leave-button-icon:hover {
    filter: opacity( 0.2);
    }
    .image-button{
        padding-left: 10px;
        width: 20px;
        height: 20px;
    }
    .image-button:hover {
        filter: opacity( 0.2);
    }

    </style>