<template>
    <BasicPopup :isOpen="namePopupOpen" @close="closeNamePopup">
        <div class =dashboard-box>
            <div class="friend-profile">
                <img :src="userAvtUrl" alt="avatar" class="avatar">
                <div class="friend-name"> {{ friend?.username }}</div>
            </div>
            <div class="level-box">
                <div class="level-indicator">
                    Level <span id="level-number">0</span>
                </div>
                <div class="level-bar-container">
                    <div class="level-bar"></div>
                </div>
            </div>
            <div class ="winning">
                <div>Winning Rate&nbsp;&nbsp;:&nbsp;&nbsp;</div>
                <div class="rate"> {{ winRate }} </div>
            </div>
        </div>
    </BasicPopup>
</template>

<script setup lang="ts">
    import { ref, inject , computed, watch } from 'vue';
    import { useUserStore, User } from '@/store/user';
    import BasicPopup from '@/components/common/BasicPopup.vue';
    import { usePopupStore} from '@/store/status';
    import { PostDashBoard } from '@/axios/api'
    
    const imgPrefix = inject('imgUrlPrefix');

    const userStore = useUserStore();

    const popupstore = usePopupStore();

    const popupname = 'FriendProfile';
    
    const namePopupOpen = computed(() => popupstore.popupname === popupname);

    const friend = ref<User>();

    const friendId : number = popupstore.getSelectFriendId;

    const friendName :string = popupstore.getSelectFriendName;


    const friendWin = ref(0);

    const friendLose = ref(0);

    const winRate = ref('0');

    let userAvtUrl = ref('');
   
    const index = userStore.user.friends.findIndex(item => item.id === friendId);
    if(index != -1)
    {
        friend.value = userStore.user.friends[index];
        if (friend.value)
            userAvtUrl.value = imgPrefix + friend.value.avatar;
    }
    else{
        if(popupstore.getSelectFriendAvt != '')
        {
            friend.value = {id : friendId, status: '',username :popupstore.getSelectName, avatar: ''};
            userAvtUrl.value = imgPrefix + popupstore.getSelectFriendAvt;
        }
    }

    const calculateWinRate = () => {
        const totalGames = friendWin.value + friendLose.value;
        if (totalGames === 0) {
            winRate.value = 'N/A';
        } else {
            const rate = (friendWin.value / totalGames) * 100;
            winRate.value = rate.toFixed(2) + '%';
        }
    };

    const setLevel = (level: number, percentage: number) => {
        const levelElement = document.getElementById("level-number");
        const levelBar = document.querySelector(".level-bar") as HTMLElement;

        if (levelElement && levelBar) {
            levelElement.textContent = level.toString();
            levelBar.style.width = `${percentage}%`;
        }
    }

    watch(() => [friendWin.value, friendLose.value], () => {
        console.log("friend calculate rate");
        calculateWinRate();
        let point = friendWin.value * 20;
        point += friendLose.value * 5;
        setLevel(point / 100, point % 100);
    });

    const closeNamePopup = () => {
        popupstore.setPopup('');
    };

    PostDashBoard(friendName, userStore.user.id).then(res =>{
        if(res)
            {
            friendWin.value = res.data.wins;
            friendLose.value = res.data.loses;
            calculateWinRate();
        }
    }).catch(() => console.log('API Error postDashboard'));

    calculateWinRate();

</script>

<style scoped>
    .dashboard-box {
        display: flex;
        flex-direction: column;
        font-family: sansation_bold;
    }

    .friend-profile {
        display: flex;
        flex-direction: row;
        align-items: center;
        width: 100%;
        height: 200px;
    }

    .friend-name {
        margin-left: 60px;
        font-size: 30px;
        color: black;
    }

    .avatar{
        width: 150px;
        height: 150px;
        border-radius: 50%;
        background-color: #e4e4e4;
    }
    .winning {
        display: flex;
        flex-direction: row;
        width: 100%;
        height: 100px;
        justify-content: center;
        align-items: center;
        color: white;
        margin-top: 10px;
        font-size: 25px;
        border-radius: 15px;
        border: solid 3px white;
        background-color: rgba(0, 0, 0, 1)
    }
    .rate {
        color: yellow;
    }

    .gamerecord {
        display: flex;
        align-items: center;
        justify-content: center;
        font-size: 15px;
        width: 100px;
        margin-top: 20px;
        padding-left: 5px;
        padding-right: 5px;
        border-top: solid white 3px;
        border-left: solid white 3px;
        border-right: solid white 3px;
        color: white;
        background-color: #20427A;
    }
    .content-list {
        max-height: 100px;
        margin-top: 0px;
        overflow-y: auto;
        border: 3px solid white;
        background-color: #3c3c3c;
    }

    .winbox {
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: center;
        height: 30px;        
        color: white;
        width: 100%;
        border-bottom: solid white 1px;
    }

    .losebox{
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: center;
        height: 30px;        
        color: white;
        width: 100%;
        border-bottom: solid white 1px;
    }

    .blue-text {
        color: blue;
    }

    .red-text {
        color: red;
    }
    .achievement {
        display: flex;
        align-items: center;
        justify-content: center;
        font-size: 15px;
        width: 100px;
        margin-top: 20px;
        padding-left: 5px;
        padding-right: 5px;
        border-top: solid white 3px;
        border-left: solid white 3px;
        border-right: solid white 3px;
        color: white;
        background-color: #20427A;
    }

    .achievement-img {
        width: 10px;
        height: 10px;
    }

    .achievement-list {
        display: flex;
        justify-content: center;
        max-height: 100px;
        flex-wrap: wrap;
        overflow-y: auto;
        border: 3px solid white;
        background-color: #e4e4e4;
    }

    .medalimg {
        width: 80px;
        height: 80px;
    }

    .achievement-item {
        display: flex;
        flex-direction: column;
        flex-shrink: 0;
        align-items: center;
        color: green;
        width: 30%;
        font-size: 10px;
        font-weight: bold;
    }    
    .level-box {
        position: relative;
        display: flex;
        flex-direction: column;
        align-items: center;
        width: 100%;
        height: 50px;
        border: solid 3px white;
        border-radius: 10px;
        background-color: #e4e4e4;
    }

    .level-indicator {
        font-size: 16px;
        font-weight: bold;
        text-align: center;
        margin-bottom: 5px;
    }

    .level-bar-container {
        width: 95%;
        height: 20px;
        background-color: white;
        border-radius: 10px;
        overflow: hidden;
    }

    .level-bar {
        height: 100%;
        width: 0;
        background-color: #01B9BB;
    }


</style>