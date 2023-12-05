<template>
  <div class="setbox">
    <div class="loading" v-if="!isLoading">loading</div>
    <div class="setprofile" v-if="isLoading">
      <div class="popupheader">
        <div class="popupname">NewUser</div>
        <div class="header_bottom"></div> 
      </div>
          <img :src="userImgUrl" class="userimg">
          <input type="file" @change="uploadFile"/>
          <input v-model="username" placeholder="Enter new username" />
          <button @click="changeProfile">Set</button>
      </div>
  </div>
</template>

<script setup lang="ts">
import axios from "axios";
import { ref, inject } from 'vue';
import { apiClient, PostSetName, PostSetAvatar } from "@/axios/api";
import { useUserStore } from "@/store/user";
import router from "@/router";

const serverUrl = `${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SERVERPORT}/auth/getToken`;
const url = new URL(window.location.href);
const id = url.searchParams.get("id");
if(!id)
  router.replace('/');
const userstore = useUserStore();

const imgPrefix = inject('imgUrlPrefix');

const isLoading = ref<boolean>(false);

let userImgUrl = ref<string>((imgPrefix + 'upload/profile/image/default.png'));

const username = ref('');

const formData = new FormData();

let hasFromData = false;

axios.post(serverUrl, { id: id })
  .then((response) => {
    const token = response.data.token;
    const tokenString = JSON.stringify(token);

    const newToken = tokenString.substring(1, tokenString.length - 1);

    const id = parseInt(response.data.id, 10);
    const newUser = { id : id, name: '', avatar: 'upload/profile/image/default.png', twofactorauth: false};


    userstore.setToken(newToken);
    apiClient.defaults.headers.common['Authorization'] = `${newToken}`;

  
    userstore.setUser(newUser);
    if(response.data.register == true)
      isLoading.value = true;
    else{
      router.replace('/home');
    }

  }).catch(error => console.log('GetToken Error'));


    const uploadFile =  async (event: Event) => {
      const file = (event.target as HTMLInputElement).files?.[0];

      if (file) {
        const reader = new FileReader();

        reader.onload = (e) => {
          if (e.target && typeof e.target.result === 'string') {
            userImgUrl.value = e.target.result;
          }
        };
        reader.readAsDataURL(file);
        formData.append('image', file);
        hasFromData = true;
      }
      };
  
    const changeProfile = async() => {
        try {
            let success = false;
            if(hasFromData)
            {
              const response = await PostSetAvatar(userstore.user.id, formData);
              if(response.status === 200)
              {
                success = true;
                hasFromData = false;
              }
            }
            if(username.value)
            {
              const response1 = await PostSetName(userstore.user.id, username.value);
              if(response1.status === 200)
                success = true;
            }
            else{
              success = false;
            }
            if (success)
            {
              router.replace('/home');
            }
          }
          catch{
            console.log('Error SetUser');
          }
      };

</script>

<style scoped>
.setbox {
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
.loading {
  color: black;
}

.setprofile {
    display: flex;
    flex-direction: column;
    height: 100%;
    gap: 5px;
}

.img-button {
    width: 38px;
    height: 38px;
    cursor: pointer;
    margin-right: 7px;
  }

  .img-button:hover {
    filter:brightness(0.2)
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

.userimg {
    width: 150px;
    height: 150px;
    border-radius: 50%;
    margin-top: 20px;
}
</style>