import { defineStore } from 'pinia'

export interface NotiBell {
  type : 'friend' | 'game' | 'not',
  userid :number,
  username : string,
}

export const usePopupStore = defineStore('popup', {
  persist: {
    enabled: true,
    strategies: [{ storage: sessionStorage }],
  },
  state: () => ({
    popupname: '',
    selectFriend : 0,
    selectName : '',
    selectFriendName: '',
    selectAvt: '',
    bells : [] as NotiBell[],
    game : {
      mode : '2d',
      roomNum : 0,
      gamestatus :'start',
      team : 0,
      width : 600,
      height : 400,
      framePerSecond : 60,
      serverY : 0,
      end: '',
      me : {
        x : 0,
        y : 0,
        width : 10,
        height :100,
        score: 0,
      },
      you : {
        userId: 0,
        x : 0,
        y : 0,        
        width : 10,
        height :100,
        score : 0
      },
      ball : {
        x : 0,
        y : 0,
        radius : 10
      }
    }
  }),
  getters: {
    getNotifications(): NotiBell[] {
      return this.bells;
    },
    getGameStatus(): string {
      return this.game.gamestatus;
    },
    getGameMyPosition() : number {
      return this.game.serverY;
    },
    getWinner() : string {
      return this.game.end;
    },
    getSelectFriendId() : number {
      return this.selectFriend;
    },
    getSelectName() : string {
      return this.selectName;
    },
    getSelectFriendAvt() : string {
      return this.selectAvt;
    },
    getSelectFriendName () : string
  {
    return this.selectFriendName;
  }},
  actions: {
    resetStore() {
      this.popupname = '';
      this.selectFriend = 0;
      this.selectName = '';
      this.selectFriendName = '';
      this.selectAvt = '';
      this.bells = [] as NotiBell[];
      this.game = {
        mode : '2d',
        roomNum : 0,
        gamestatus :'start',
        team : 0,
        width : 600,
        height : 400,
        framePerSecond : 60,
        serverY : 0,
        end: '',
        me : {
          x : 0,
          y : 0,
          width : 10,
          height :100,
          score: 0,
        },
        you : {
          userId: 0,
          x : 0,
          y : 0,        
          width : 10,
          height :100,
          score : 0
        },
        ball : {
          x : 0,
          y : 0,
          radius : 5
        }
      }
    },
    setPopup(usepopupname : string) {
        this.popupname = usepopupname;
    },

    setNotiBell(newNoti : NotiBell){
      this.bells.push(newNoti);
    },

    deleteNotification(index : number) {
      this.bells.splice(index, 1);
    },
    setSelectFriend(id :number) {
      this.selectFriend = id;
    },
    setSelectFriendName(name :string) {
      this.selectFriendName = name;
    },   
    setSelectName(name :string) {
      this.selectName = name;
    },
    setSelectAvatar(avt :string) {
      this.selectAvt = avt;
    },
    //game
    setGameMode(gameMode : string) {
      this.game.mode = gameMode;
    },
    setFrame(frame : number) {
      this.game.framePerSecond = frame;
    },
    setGameStatus(status : string) {
      this.game.gamestatus = status;
    },
    setServerY(serverY : number) {
      this.game.serverY = serverY;
    },
    setGame(obj : { roomNum :number , team : number, userId : number}) {
      this.game.roomNum = obj.roomNum;
      this.game.team = obj.team;
      this.game.you.userId = obj.userId;
    },

    setMyPaddle( y : number) {
      this.game.me.y = y;
    },

    setGameWinner( team :number) {
      if (team === 0)
      {
        this.game.end = 'Red';
      }
      else{
        this.game.end = 'Blue';
      }
    },

    setGameUpdate( res : any) {
      if(this.game.team == 0)//red
      {
        this.game.me.x = res.red.x;
        this.game.me.width = res.red.width;
        this.game.me.height = res.red.height;
        this.game.me.score = res.red.score;

        this.game.you.x = res.blue.x;
        this.game.you.y = res.blue.y;
        this.game.you.width = res.blue.width;
        this.game.you.height = res.blue.height;
        this.game.you.score = res.blue.score;

      }
      else{ //blue
        this.game.me.x = res.blue.x;
        this.game.me.width = res.blue.width;
        this.game.me.height = res.blue.height;
        this.game.me.score = res.blue.score;

        this.game.you.x = res.red.x;
        this.game.you.y = res.red.y
        this.game.you.width = res.red.width;
        this.game.you.height = res.red.height;
        this.game.you.score = res.red.score;
      }
      this.game.width = res.stadium.width;
      this.game.height = res.stadium.height;

      this.game.ball.x = res.ball.x;
      this.game.ball.y = res.ball.y;
      this.game.ball.radius = res.ball.radius;
    }
  }
})