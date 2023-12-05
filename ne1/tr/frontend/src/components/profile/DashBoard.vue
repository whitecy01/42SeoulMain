<template>
    <BasicPopup :isOpen="namePopupOpen" @close="closeNamePopup">
        <div class =dashboard-box>
            <div class ="winning">
                <div>Winning Rate&nbsp;&nbsp;:&nbsp;&nbsp;</div>
                <div class="rate"> {{ winRate }} </div>
            </div>
            <div class="level-box">
                <div class="level-indicator">
                    Level <span id="level-number">0</span>
                </div>
                <div class="level-bar-container">
                    <div class="level-bar"></div>
                </div>
            </div>
            <div class="gamerecord">Game Record</div>
            <div class="content-list">
                <div v-for="(item, index) in contentList" :key="index" :class="{ 'winbox': item.history_isUserWin === true, 'losebox': item.history_isUserWin === false }">
                    {{ myName }}
                    &nbsp;&nbsp;VS&nbsp;&nbsp;
                    {{ item.opponent_username }}&nbsp;&nbsp;
                    <span :class="{ 'red-text': item.history_isUserWin === true, 'blue-text': item.history_isUserWin === false }">
                        {{ toResult(item.history_isUserWin) }}
                    </span>
                </div>
            </div>
            <div class="achievement">
                Achivement
                <img src="/medal.png" class="achievement-img">
            </div>
            <div class="achievement-list">
                <div v-for="achievement in achievements" :key="achievement.id" class="achievement-item">
                    <img :src="achievement.avt" class="medalimg">
                    <div>{{ achievement.name }}</div>
                </div>
            </div>
        </div>
    </BasicPopup>
</template>

<script setup lang="ts">
    import { ref, computed, watch } from 'vue';
    import { useUserStore, History } from '@/store/user';
    import BasicPopup from '@/components/common/BasicPopup.vue';
    import { usePopupStore } from '@/store/status';
    import { PostDashBoard, PostGameHistory } from '@/axios/api';

    interface achievement {
        id: number, name: string , avt: string
    }

    const achievements = ref<achievement[]>([]);

    const contentList = ref<History[]>([]);

    const userStore = useUserStore();

    const myName = ref(userStore.user.name);

    const popupStore = usePopupStore();

    const popupname = 'DashBoard';

    const namePopupOpen = computed(() => popupStore.popupname === popupname);

    const winRate = ref('0');

    PostDashBoard(userStore.user.name, userStore.user.id).then(res =>{
        if(res?.status == 200)
            userStore.setDashBoard(res?.data);
    }).catch(error => console.log('API Error postDashboard'));

    PostGameHistory(userStore.user.id).then(res => {
        if(res?.status == 200)
        {
            userStore.setGameHistory(res?.data);
            contentList.value =res?.data;
            checkAchievement();
        }
    }).catch(error => console.log('API Error postGameHistory'));

    const toResult = (isWin : boolean) => {
        if (isWin)
            return 'Win'
        else
            return 'Lose'
    }

    const setLevel = (level: number, percentage: number) => {
        const levelElement = document.getElementById("level-number");
        const levelBar = document.querySelector(".level-bar") as HTMLElement;

        if (levelElement && levelBar) {
            levelElement.textContent = level.toString();
            levelBar.style.width = `${percentage}%`;
        }
    }

    watch(() => userStore.getGamehistory,
    (history) => {
      if(history)
      {
        let point = history.win * 20;
        point += history.lose * 5;
        setLevel(point / 100, point % 100);
      }
    });

    const calculateWinRate = () => {
        const totalGames = userStore.user.win + userStore.user.lose;
        if (totalGames === 0) {
            winRate.value = 'N/A';
        } else {
            const rate = (userStore.user.win / totalGames) * 100;
            winRate.value = rate.toFixed(2) + '%';
        }
    };

    const checkAchievement = () => {
        let winningStreak = 0;
        achievements.value = [];
        for(let i = contentList.value.length - 1; i >= 0; i--)
        {
            if (contentList.value[i].history_isUserWin == true)
            {
                winningStreak++;
            }
            else
                winningStreak = 0;
        }
        if(winningStreak >= 10)
            achievements.value.push({ id: 3, name: '10연승 달성', avt: '/goldtrophy.png'});
        else if (winningStreak >= 3)
            achievements.value.push({ id: 3, name: '3연승 달성', avt: 'brasstrophy.png'});
        if (userStore.user.win >= 1)
            achievements.value.push({ id: 3, name: '1승 달성', avt: '/1win.png'});
        if (userStore.user.win >= 10)
            achievements.value.push({ id: 3, name: '10승 달성', avt: '/10win.png'});
    }

    calculateWinRate();
    checkAchievement();
    
    watch(() => [userStore.user.win, userStore.user.lose], () => {
        calculateWinRate();
    });

    const closeNamePopup = () => {
        popupStore.setPopup('');
    };

</script>

<style scoped>
    .dashboard-box {
        display: flex;
        flex-direction: column;
        font-family: sansation_bold;
        
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
        min-height: 60px;
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
        background-color: #acacac;
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
        background-color: #acacac;
        border-bottom: solid white 1px;
    }

    .blue-text {
        color: rgb(0, 136, 255);
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
        min-height: 60px;
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
        margin-top: 20px;
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