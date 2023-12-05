<template>
    <div class ="inputBox">
        <div class="entermsg"> 
            <input class="msginput" v-model="message">
            <button class="send-bt" @click="emitSendMsg">send</button>
        </div>
    </div>
</template>

<script setup lang="ts">
    import {ref } from 'vue'

    const message = ref<string>('');

    const emit = defineEmits(['sendMsg']);

    const emitSendMsg= () => {
        if (message.value != '')
        {
            emit('sendMsg', message.value);
            message.value = '';
        }
    }
</script>

<style scoped>

    .inputBox {
        position: relative;
        padding-bottom: 0;
        width: 100%;
    }
    .entermsg {
        position: relative;
        display: flex;
        flex-direction: row;
        width: 95%;
        left: 2.5%;
        padding-bottom: 3px;
    }


    .msginput {
        width: 85%;
        height: 20px;
    }

    .send-bt {
        width: 15%;
        height: auto;
        font-family: sansation_bold;
    }

</style>