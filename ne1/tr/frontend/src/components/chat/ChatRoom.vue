<template>
    <ChatItem v-for="message in messages" @contextmenu.prevent="event => handleContextMenu(message, event)"
        :key="message.id"
        :type="message.type"
        :id="message.id"
        :name="message.name"
        :avatar="message.avatar"
        :message="message.message"
    />
    <ExtraChatList v-if="selectMsg" 
        :visible="extraPopupVisible"         
        :channel="channel"
        :position="chatPosition" 
        :select="selectMsg" @mouseleave="closeChat" />
</template>
    
  <script lang="ts" setup>
    import ChatItem from './ChatItem.vue';
    import ExtraChatList from './ExtraChatList.vue';
    import { ref , watch, computed} from 'vue';
    import { Channel, Msg, useUserStore } from '@/store/user';

    const props = defineProps<{channel: Channel}>();

    const userstore = useUserStore();

    const myName = userstore.user.name;
  
    const messages = ref<Msg[]>(props.channel.message);

    const extraPopupVisible = ref(false);

    const chatPosition = ref({ x: '0px', y: '0px' });

    const selectMsg = ref<Msg>();

    const index = computed(() => userstore.user.Channels.findIndex(item => item.roomname === props.channel.roomname));
    if (index.value != -1)
    {
        userstore.setReadChannel(props.channel.roomname);
        watch(() => userstore.user.Channels[index.value]?.unread,
        () =>  userstore.setReadChannel(props.channel.roomname));
    }

    const handleContextMenu = (user: Msg, event: MouseEvent) => {
        if(user.name != myName){
            chatPosition.value.x = `${event.pageX}px`;
            chatPosition.value.y = `${event.pageY}px`;
            extraPopupVisible.value = true;
            selectMsg.value = user;
        }
    };

    const closeChat = () => {
        extraPopupVisible.value = false;
    }

  </script>

    