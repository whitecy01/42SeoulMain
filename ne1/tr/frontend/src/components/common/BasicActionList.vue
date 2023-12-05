<template>
  <div v-if="isvisible" class="lists" :style="computedStyle()">
    <slot></slot>
  </div>
  </template>
  
  <script setup lang="ts">
  import { StyleValue } from 'vue';
  
  interface Position {
    x : string;
    y : string;
  }

  interface Props {
    isvisible: boolean;
    mousePosition: Position;
  }
  
  const props = defineProps<Props>();
    
  const computedStyle = ():StyleValue => ({
    position: 'fixed',
    top: `${props.mousePosition.y}`,
    left: `${props.mousePosition.x}`,
    backgroundColor: 'darkgray',
    color: 'white',
    padding: '4px',
    'padding-left': '10px',
    'padding-right': '10px',
    'border-radius': '4px',
    'z-index': '999'
  });

  </script>
  
  <style scoped>
  .lists {
    display: flex;
    flex-direction: column;
    justify-content: center;
    font-weight: bold;
  }
  .lists :hover {
    filter: brightness(0.1);
  }
</style>