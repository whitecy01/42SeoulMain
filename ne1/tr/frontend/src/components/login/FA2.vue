<template>
  <div class="container">
    <div class="center">
      <div class="header">
        <img src="/googleAuth.png" class="logo">
        <div class="title">Google Authenticator</div>
      </div>
      <img :src="otpAuthUrl" alt="QR Code" />
      <input class="codeinput" v-model="authcode" type="text" placeholder="인증 코드(숫자)" />
      <div class="check-bt" @click="saveAuthcode">Check</div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from "vue";
import axios from "axios";
import QRCode from "qrcode";
import { useUserStore } from "@/store/user";
import router from "@/router";
import { apiClient } from "@/axios/api";

const authcode = ref<string | null>(null);
const otpAuthUrl = ref("");
const userstore = useUserStore();

const fetchOtpAuthUrl = async () => {
  const url = new URL(window.location.href);
  const id = url.searchParams.get("id");
  if (!id)
    router.replace('/');
  axios.post(`${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/auth/getOtpAuthUrl`, { id: id })
    .then((response) => {
        const data = response.data.otpAuthUrl;
        QRCode.toDataURL(data, (error, url: string) => {
          if (error) {
            console.error(error);
          } else {
            otpAuthUrl.value = url;
          }
        });
    })
    .catch((error) => {
      console.error("Error occurred:", error);
    })
};
onMounted(() => {
  fetchOtpAuthUrl();
});

const saveAuthcode = () => {
  const current_url = new URL(window.location.href);
  const userId = current_url.searchParams.get("id");
  const authUrl = `${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/auth/verify?twoFactorAuthCode=${authcode.value}`;
  const tokenUrl = `${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/auth/getToken`;
  axios.post(authUrl, { id: userId })
    .then((response) => {
      if (response.status === 200) {
        console.log("Authentication successful");
        axios.post(tokenUrl, { id: userId })
          .then((response) => {
            const token = response.data.token;
            const tokenString = JSON.stringify(token);
            const newToken = tokenString.substring(1, tokenString.length - 1);
            const id = parseInt(response.data.id, 10);
            const newUser = { id: id, name: '', avatar: '', twofactorauth: true };
            userstore.setToken(newToken);
            apiClient.defaults.headers.common['Authorization'] = `${newToken}`;
            userstore.setUser(newUser);
            router.replace('/home');
          }).catch((error) => {
            console.error("Error occurred:", error);
          })
      } else {
        console.error("Authentication failed");
      }
    })
    .catch((error) => {
      console.error("Error occurred:", error);
    });
};
</script>

<style>
.container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 100vh;
}

.header {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  width: 100%;
  height: 50px;
  margin-top: 20px;
}

.title {
  margin-left: 10px;
  font-size: larger;
  font-weight: bolder;
}

.codeinput {
  margin-top: 10px;
}

.logo {
  width: 30px;
  height: 30px;
  left: 30px;
}

.check-bt {
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: #4285F4;
  width: 80px;
  height: 25px;
  margin-top: 10px;
  font-size: 15px;
  font-weight: bolder;
  color: white;
}

.check-bt:hover {
  filter: brightness(1.2);
}

.center {
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 300px;
  background-color: aliceblue;
  border-radius: 10px;
  margin-top: 20px;
  padding-bottom: 20px;
}
</style>
