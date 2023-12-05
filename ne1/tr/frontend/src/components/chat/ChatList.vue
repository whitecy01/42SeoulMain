<template>
    <div class="channelList">
        <transition-group name="list" tag="div">
        <div v-for="channel in channels" :key="channel.roomname" :class="{'channel': channel.type === 'msg', 'DM': channel.type === 'dm'}"
            @click="emitChannel(channel)">
            <div class="name">
                <div class="avt-box">
                    <div v-for="(member, index) in channel.member" 
                    :key="index"
                    :style="{ zIndex: channel.member.length - index }">
                        <img v-if="index < 5" :src="imgPrefix+member.avatar" art="avtar" class="member-avt">
                    </div>
                </div>
                {{ truncate(channel.roomname) }}
                <div class="members" v-if="channel.type != 'dm'">({{ channel.member.length }})</div>
            </div>
            <div v-if="channel.unread > 0" class="unread">{{ channel.unread }}</div>
        </div>
        </transition-group>
    </div>
</template>
  
<script setup lang="ts">

    import { inject, computed } from 'vue'
    import { useUserStore, Channel } from '@/store/user';

    const userstore = useUserStore();
    
    const channels = computed(() => userstore.getChannelsList);

    const emit = defineEmits(['select']);

    const emitChannel = (channel : Channel) => {
        emit('select', channel);
    }
    
    const imgPrefix = inject('imgUrlPrefix');

    const truncate = (str :string) => {
        return str.length > 15 ? str.substring(0, 15) + '...' : str;
    }
</script>
  
<style scoped>
.channelList {
    margin-top: 10px;
    margin-bottom: 10px;
    height: 100%;
    text-align: left;
    overflow-y: auto;
}

.unread {
    display: flex;
    justify-content: center;
    align-items: center;
    margin-right: 15px;
    width: 20px;
    height: 20px;
    border-radius: 50%;
    font-size: 11px;
    background-color: rgb(255, 0, 0);
    color:white;
}
.channel {
    display: flex;
    justify-content: space-between;
    flex-direction: row;
    align-items: center;
    background: #e2baba;
    margin-bottom: 5px;
    border-radius: 8px;
    width: 100%;
    height: 70px;
    font-size: 20px;
}

.DM {
    display: flex;
    justify-content: space-between;
    flex-direction: row;
    align-items: center;
    background: #99b7e6;
    margin-bottom: 5px;
    border-radius: 8px;
    width: 100%;
    height: 70px;
    font-size: 20px;
}
.DM:hover{
    background: rgb(255,255,255);
    background: linear-gradient(90deg, rgba(255,255,255,1) 0%, rgba(130,130,255,1) 35%, rgba(0,208,250,1) 100%);
}

.channel:hover{
    background: rgb(255,255,255);
    background: linear-gradient(90deg, rgba(255,255,255,1) 0%, rgba(255,0,0,1) 50%, rgba(218,148,50,1) 100%);
}

.name {
    position: relative;
    margin-left: 10px;
    display: flex;
    flex-direction: row;
    align-items: center;
}

.avt-box {
    position: relative;
    display: flex;
    margin-left: 10px;
}
.member-avt{
    width: 20px;
    height: 20px;
    border-radius: 50%;
    margin-left: -12px;
    background-color: white;
}
.members {
    margin-left: 5px;
    font-size: 12px;
    
}
.list-move {
    transition: transform 0.5s;
}
</style>
  