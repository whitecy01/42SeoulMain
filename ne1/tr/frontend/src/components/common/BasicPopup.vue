<template>
  <div v-if="isOpen" class="popup">
    <div class="popupheader">
      <div class="popupname">{{ popupstore.popupname }}</div>              
      <img src="/close.png" alt="Close" class="close-btn" @click="closePopup" />
      <div class="header_bottom"></div>
    </div>
    <div class="content">
      <slot></slot>
    </div>
  </div>
</template>

<script lang="ts" setup>
import { usePopupStore } from '@/store/status';

defineProps<{ isOpen: boolean }>();

const emits = defineEmits(['close']);

const popupstore = usePopupStore();

const closePopup = () => {
  emits('close');
}
</script>

<style scoped>
.popup {
  position: fixed;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width:400px;
  padding: 20px;
  background-color: rgba(245, 245, 245, 0.8);
  border: 1px solid #ddd;
  z-index: 888;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5);

}

.popupheader {
  display: flex;
  position:absolute;
  top: 0%;
  left: 0%;
  width: 100%;
  height: 35px;
  background-color: #20427A;
}

.content {
  position: relative;
  top: 20px;
  padding-bottom: 10px;
}

.popupname {
  position: absolute;
  top: 5px;
  left: 10px;
  font-family: sansation_bold;
  color: white;
}

.header_bottom {
  position: absolute;
  width: 100%;
  height: 4px;
  bottom: 0;
  background-color: white;
}
.close-btn {
  position: absolute;  
  top: 10px;          
  right: 10px;        
  cursor: pointer;
  width: 14px;
  height: 14px;
}

.close-btn:hover {
  filter: brightness(0.7);
}
</style>

