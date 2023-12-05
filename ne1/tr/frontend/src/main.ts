import { createApp } from 'vue'
import App from './App.vue'
import router from './router/index'
import { createPinia } from 'pinia'
import piniaPersist from "pinia-plugin-persist";

const pinia = createPinia();
pinia.use(piniaPersist);

const app = createApp(App).use(pinia).use(router);

app.provide('imgUrlPrefix', `${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/`);

app.mount('#app');

