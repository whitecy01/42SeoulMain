<template>
    <div>
      <BasicPopup :isOpen="popupOpen" @close="closePopup">
        <input type="file" ref="fileInput" accept="image/*" @change="handleFileChange" />
      </BasicPopup>
      <button @click="openImagePopup" class="change-image-button">Change Image</button>
    </div>
</template>
  
<script setup lang="ts">
  import { ref } from 'vue';
  import BasicPopup from '@/components/common/BasicPopup.vue';
  
  const popupOpen = ref(false);
  const fileInputRef = ref<HTMLInputElement | null>(null);
  
  const openImagePopup = () => {
    popupOpen.value = true;
  };
  
  const closePopup = () => {
    popupOpen.value = false;
  };
  
  const handleFileChange = (event: Event) => {
    const input = event.target as HTMLInputElement;
    if (input.files && input.files.length > 0) {
      const selectedFile = input.files[0];
      const imageUrl = URL.createObjectURL(selectedFile);
      // 이 부분에서 imageUrl을 어떻게 활용할 지, profileButton의 이미지를 어떻게 교체할 지 구현해야 합니다.
      console.log('Selected image URL:', imageUrl);
    }
    closePopup();
  };
</script>
  