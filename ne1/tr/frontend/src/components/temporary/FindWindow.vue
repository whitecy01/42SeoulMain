<template>
  <div class="find-window">
    <img class="close-button-icon1" alt="" src="/close-button1.svg" />
    <div class="find-button">
      <div class="find-button1" />
      <div class="find">Find</div>
    </div>
    <div class="list-window" />
  </div>
</template>

<script lang="ts">
  import { defineComponent, ref } from "vue";

  export default defineComponent({
    name: "FindWindow",
  });
</script>

<style scoped>
  .close-button-icon1 {
    position: absolute;
    top: 20px;
    left: 470px;
    width: 20px;
    height: 20px;
  }
  .find-button1 {
    position: absolute;
    top: 0px;
    left: 0px;
    background-color: var(--color-dimgray);
    width: 120px;
    height: 30px;
  }
  .find {
    position: absolute;
    top: 3px;
    left: 13px;
    display: flex;
    align-items: center;
    justify-content: center;
    width: 97px;
    height: 23px;
  }
  .find-button {
    position: absolute;
    top: 250px;
    left: 370px;
    width: 120px;
    height: 30px;
  }
  .list-window {
    position: absolute;
    top: 60px;
    left: 50px;
    background-color: var(--color-darkgray);
    width: 400px;
    height: 170px;
  }
  .find-window {
    position: relative;
    border-radius: var(--br-mini);
    background-color: var(--color-gainsboro);
    width: 100%;
    height: 300px;
    overflow: hidden;
    text-align: center;
    font-size: var(--font-size-xs);
    color: var(--color-white);
    font-family: var(--font-inter);
  }
</style>
