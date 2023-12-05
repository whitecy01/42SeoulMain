<template>
    <div class="avatar-icon">
      <img :src="user.avatar" alt="avatar" class="avatar-image" @click="openImagePicker"/>
      <!-- <BasicPopup :isOpen="popupOpen" @close="closePopup">
        <input type="file" ref="fileInput" accept="image/*" @change="handleFileChange" />
      </BasicPopup> -->
    </div>
</template>
  
<script setup lang="ts">
  import { ComputedRef, computed, ref } from 'vue';
  // import BasicPopup from '@/components/BasicPopup.vue';
  import { usePopupStore } from '@/store/status'
  import { useUserStore } from '@/store/user';
  

  const userStore = useUserStore();
  const userRef = ref(userStore.user);
  const user = userRef.value;
  const popupStore = usePopupStore();
  const popupname  = 'AvatarButton';

  const popupOpen = computed(()=> popupStore.popupname === popupname);

  const openImagePicker = () => {
    
    popupStore.setPopup(popupname);
  };

  const closePopup = () => {
    popupStore.setPopup('');

  };
  
  const handleFileChange = (event: Event) => {
    // const input = event.target as HTMLInputElement;
    // if (input.files && input.files.length > 0) {
    //   const selectedFile = input.files[0];
    //   user.avatar = URL.createObjectURL(selectedFile);
    // }
    closePopup();
  };
</script>

<style scoped>
  
  
  .avatar-image {
    width: auto;
    height: auto;
    max-width: 100%;
    max-height: auto;    
    border-radius: 50%;
  }
</style>