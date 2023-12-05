<template>
    <div class="find-button-icon">
        <img src="/roomlist.png" alt="x" class="image" @click="openFindWindow" />
        <BasicPopup :isOpen="popupOpen" @close="closePopup">
            <div class="channel-list-container" @scroll="handleScroll">
                <div v-for="channel in visibleChannels" :key="channel.name" class="popup-content"
                    @click="extraPopup(channel)">
                    <div class="name">{{ channel.name }}</div>
                    <img v-if="channel.status == 'private'" src="/lock.png" class="lock-img">
                </div>
                <div class="load" v-if="isLoad">Loading</div>
            </div>
            <div class ="find">
                <input class="find-input" placeholder="Enter channel" v-model="channelName">
                <button @click="findChannel" class="find_bt">Find</button>
            </div>
        </BasicPopup>
        <ChannelPopup :isOpen="extraPopupVisible" :select="selectChannel" @close="closeChannel"/>
    </div>
</template>

<script setup lang="ts">
    import { ref, computed } from 'vue';
    import BasicPopup from '@/components/common/BasicPopup.vue';
    import ChannelPopup from '@/components/chat/ChannelPopup.vue'
    import { usePopupStore } from '@/store/status';
    import { GetChannelList }from '@/axios/api'
    import { useUserStore } from '@/store/user';

    const channelName = ref<string>('');

    const popupStore = usePopupStore();

    const popupname  = 'ChannelFind';

    const popupOpen = computed(()=> popupStore.popupname === popupname);

    const channels = ref<Array<{ name: string ,status: 'public' | 'private'}>>([]);

    const isLoad = ref<boolean>(false);

    const selectChannel = ref<{name: string, status:'public' | 'private'}>({name :'' , status: 'public'});

    const visibleChannelCount = ref(8);

    const hasMoreData = computed(() => visibleChannelCount.value < channels.value.length);

    const visibleChannels = computed(() => channels.value.slice(0, visibleChannelCount.value));

    const getChannelList = async () => {
        try {
            const response = await GetChannelList(useUserStore().user.id);
            if (response.status === 200) {
                channels.value = response.data;
            }
        } catch {
            console.error('Error Channel');
        }
    }

    const findChannel = () => {
        const findChannel = channels.value.find(channel => channel.name === channelName.value);
        if (findChannel)
        {            
            selectChannel.value = findChannel;
            extraPopupVisible.value = true;
        }
        else {
            extraPopupVisible.value = false;
            console.log("NOT FOUND");
        }
        channelName.value = '';
    }

    const extraPopupVisible = ref(false);

    const extraPopup = (Channel: { name: string, status:'public' | 'private' }) => {
        extraPopupVisible.value = true;
        selectChannel.value = Channel;
    };

    const closeChannel = () => {
        extraPopupVisible.value = false;
        popupStore.setPopup('');
    }

    const handleScroll = (event: Event) => {
        const container = event.target as HTMLElement;
        if (container.scrollTop + container.clientHeight >= container.scrollHeight && hasMoreData.value) {
            visibleChannelCount.value += 8;
        }
    };

    const openFindWindow = () => {
        isLoad.value=true;
        channels.value = [];
        getChannelList().then(() => isLoad.value = false);
        popupStore.setPopup(popupname);
    };

    const closePopup = () => {
        popupStore.setPopup('');
        extraPopupVisible.value = false;
    };
</script>

<style scoped>
.find-button-icon {
        position: relative;
        display: flex;
        align-items: center;
        min-width: 23px;
        min-height: 23px;
        width: 16%;
    }

.image {
    position: absolute;
    top: 50%;
    left: 50%;
    width: 100%;
    transform: translate(-50%, -50%);
    max-width: 100%;
    max-height: auto;
}

.name {
    margin-left: 10px;
}
.image:hover {
    filter: opacity( 0.2);
}

.load{
    display: flex;
    justify-content: center;
    align-items: center;
    font-family: 'Courier New', Courier, monospace;
    font-size: 12px;
    font-weight: bold;
    color: black;
}
.channel-list-container {
  margin-top: 10px;
  margin-bottom: 10px;
  height: 350px;
  text-align: left;
  overflow-y: auto;
}

.popup-content {
    display: flex;
    justify-content: space-between;
    flex-direction: row;
    align-items: center;
    background: rgba(255,255,255,1);
    margin-bottom: 5px;
    border-radius: 8px;
    width: 100%;
    height: 50px;
}

.popup-content:hover{
    background-color:#01B9BB;
}

.lock-img {
    width: 20px;
    height: 20px;
    margin-right : 15px;
    filter: opacity(0.5);
}
.find {
    display: flex;
    width: 100%;
    justify-content: center;
}

.find-input {
    width: 70%;
}
.find_bt {
    margin-left: 12px;
    width: 22%;
    height: auto;
}
</style>