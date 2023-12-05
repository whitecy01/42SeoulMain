import { createRouter, createWebHistory } from 'vue-router';
import LoginPopupVue from '@/components/login/LoginPopup.vue';
import MainPageVue from "@/views/MainPage.vue";
import CheckLogin from "@/components/login/CheckLogin.vue";
import fa2 from "@/components/login/FA2.vue";

const routes = [
    { path: '/', component:LoginPopupVue},
    { path: '/callback', component:CheckLogin},
    { path: '/home', component:MainPageVue},
    { path: '/fa2', component:fa2},
]

const router = createRouter({
    history: createWebHistory(),
    routes
});

export default router;
