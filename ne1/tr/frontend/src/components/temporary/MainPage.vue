<template>
    <ProfileLayout />
    <div class="content">
        <PingPong/>
        <ChatLayout/>
    </div>
</template>


<script setup lang="ts">
    import PingPong from '@/components/game/PingPong.vue';
    import ChatLayout from '@/components/chat/ChatLayout.vue';
    import ProfileLayout from '@/components/profile/ProfileLayout.vue';
</script>

<style scoped>

  .content {
    display: flex;
  }

</style>