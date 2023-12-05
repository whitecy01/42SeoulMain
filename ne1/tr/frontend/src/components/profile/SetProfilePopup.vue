<template>
    <img src="/gear.png" alt="setting" @click="() => openPopup()" class="img-button" />
    <BasicPopup :isOpen="popupOpen" @close="closePopup">
    <label class="switch" v-if="!isGamming">
      <div class="leftmode">3D Game</div>
      <input type="checkbox" :checked="is3d" @change="toggleSwitch" ref="toggleBtn">
      <span class="slider round"></span>
    </label>
    <label class="switch2" v-if="!isGamming">
      <div class="leftmode">HighFrame</div>
      <input type="checkbox" :checked="isHighFrame" @change="FrametoggleSwitch" ref="toggleBtn2">
      <span class="slider round"></span>
    </label>
    <label class="switch3">
      <div class="leftmode">2FA</div>
      <input type="checkbox" :checked="is2Fa" @change="Fa2Switch" ref="toggleBtn3">
      <span class="slider round"></span>
    </label>
      <div class="setprofile">
        <img :src="userImgUrl" class="userimg">
        <input type="file" @change="uploadFile"/>
        <input v-model="username" placeholder="Enter new username" />
        <button @click="changeProfile">Set</button>
      </div>
    </BasicPopup>
  </template>
  
  <script setup lang="ts">
    import { ref , computed , inject} from 'vue';
    import BasicPopup from '@/components/common/BasicPopup.vue';
    import { usePopupStore } from '@/store/status';
    import { useUserStore } from '@/store/user';
    import { PostSetName, PostSetAvatar, Post2FaSwich , fetchData} from '@/axios/api';

    const userstore = useUserStore();

    const imgPrefix = inject('imgUrlPrefix');

    let userImgUrl = ref('');

    const username = ref('');

    const popupStore = usePopupStore();

    const popupname  = 'Setting';

    const popupOpen = computed(()=> popupStore.popupname === popupname);

    const isGamming = computed(()=> popupStore.game.gamestatus !== 'start');

    const is3d = computed(() => popupStore.game.mode === '3d');

    const isHighFrame = computed(() => popupStore.game.framePerSecond >= 60);

    const is2Fa = computed(() => userstore.user.twoFa == true);

    const openPopup = () => {
      userImgUrl.value = imgPrefix + userstore.user.avatar;
      popupStore.setPopup(popupname);
    }

    const closePopup = () => {
      popupStore.setPopup('');
    }

    const formData = new FormData();

    let hasFromData = false;

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
            if(username.value && userstore.user.name != username.value)
            {
              const response1 = await PostSetName(userstore.user.id, username.value);
              if(response1.status === 200)
                success = true;
            }
            if (success)
            {
              fetchData(userstore.user.id).then(res =>{
                  if(res)
                  {
                      userstore.setUser({
                      id: res.id,
                      name: res.username,
                      avatar: res.avatar,
                      twofactorauth : res.twofactorauth
                      })
                  }
                  }).catch(() => {
                      console.log("ERROR SetUser FETCH");
                  });
            }
          }
          catch{
            console.log('Error SetUser');
          }
      };

      const toggleBtn = ref<HTMLInputElement | null>(null);

      const toggleBtn2 = ref<HTMLInputElement | null>(null);

      const toggleBtn3 = ref<HTMLInputElement | null>(null);

      const toggleSwitch = () => {
        if (toggleBtn.value?.checked) {
          popupStore.setGameMode('3d');
        } else {
          popupStore.setGameMode('2d');
        }
      };

      const FrametoggleSwitch = () => {
        if (toggleBtn2.value?.checked) {
          popupStore.setFrame(60);
        } else {
          popupStore.setFrame(20);
        }
      };

      const Fa2Switch = () => {
        if (toggleBtn3.value?.checked) {
            Post2FaSwich('on', userstore.user.id).then(res => {
            if(res?.status == 200)
              userstore.setTwoFa(res.data.twoFactorAuth);
          });
        } else {
            Post2FaSwich('off', userstore.user.id).then(res => {
            if(res?.status == 200)
              userstore.setTwoFa(res.data.twoFactorAuth);
          });
        }
      }

  </script>
<style scoped>
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

.userimg {
    width: 150px;
    height: 150px;
    border-radius: 50%;
}

.switch {
  position: absolute;
  display: inline-block;
  top: 10px;
  right: 0px;
  width: 40px;
  height: 24px;
  z-index: 999;
}

.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}

.switch2 {
  position: absolute;
  display: inline-block;
  top: 40px;
  right: 0px;
  width: 40px;
  height: 24px;
  z-index: 999;
}
.switch2 input {
  opacity: 0;
  width: 0;
  height: 0;
}

.switch3 {
  position: absolute;
  display: inline-block;
  top: 70px;
  right: 0px;
  width: 40px;
  height: 24px;
  z-index: 999;
}
.switch3 input {
  opacity: 0;
  width: 0;
  height: 0;
}

.leftmode {
  position: absolute;
  width: fit-content;
  top : 5px;
  left : -60px;
  font-family: sansation_bold;
  font-size: 11px;
}


.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #3c3c3c;
  transition: .4s;
  border-radius: 24px;
}

.slider:before {
  position: absolute;
  content: "";
  height: 16px;
  width: 16px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  transition: .4s;
  border-radius: 50%;
}
input:checked + .slider {
  background-color: #2196F3;
}

input:checked + .slider:before {
  transform: translateX(16px);
}

.slider.round {
  border-radius: 24px;
}

.slider.round:before {
  border-radius: 50%;
}

</style>