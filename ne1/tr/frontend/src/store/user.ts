import { defineStore } from 'pinia'
import { GetFriendsList, GetBlocksList, PostUpdateMembers } from '@/axios/api'; 
import { usePopupStore } from './status';

export interface Msg {
  type :'message' | 'notification',
  id : number,
  name : string, 
  avatar: string,
  message: string
}

export interface Channel {
  type: 'msg' | 'dm' | 'not',
  roomname: string,
  status: 'private' | 'public',
  admin: string[],
  owner: string,
  member: User[],
  message: Msg[],
  unread : number
}

export interface User {
  id: number;
  status: string;
  username: string;
  avatar: string;
}

export interface Block {
  id :number;
  username : string;
}

export interface History { opponent_username : string, history_isUserWin : boolean}

export interface gameHistory {
  win : number,
  lose : number,
  gameHistory : History[]
}

export const useUserStore = defineStore('user', {
  persist: {
    enabled: true,
    strategies: [{ storage: sessionStorage }],
  },
  state: () => ({
    user: {
        id: 0,
        name: '',
        avatar: '',
        friends: [] as User[],
        Channels: [] as Channel[],
        blocks: [] as Block[],
        token:'',
        win: 0,
        lose: 0,
        gameHistory : [] as History[],
        twoFa : false
    }
  }),

  getters: {
    getFriends(): User[] {
      return this.user.friends;
    },
    getBlocks(): Block[] {
      return this.user.blocks;
    },
    getChannelsList(): Channel[] {
      return this.user.Channels;
    },

    getChatRoom() : Channel | undefined{
      return this.user.Channels.find(t=>t.type === "msg");
    },

    getGamehistory() : gameHistory {
      const ret =  {
        win : this.user.win,
        lose : this.user.lose,
        gameHistory : this.user.gameHistory
      }
      return ret;
    }

  },

  actions: {
    resetStore(){
      this.user = {
        id: 0,
        name: '',
        avatar: '',
        friends: [] as User[],
        blocks: [],
        Channels: [] as Channel[],
        token:'',
        win: 0,
        lose: 0,
        gameHistory : [] as History[],
        twoFa : false
      };
    },
    setUser(newUser: { id: number; name: string; avatar: string; twofactorauth : boolean;}) {
        this.user.id = newUser.id;
        this.user.name = newUser.name;
        this.user.avatar = newUser.avatar;
        this.user.twoFa = newUser.twofactorauth;
    },

    setUserName(newName :string) {
      this.user.name = newName;
    },

    setUserAvatar(newAvatar : string) {
      this.user.avatar = newAvatar;
    },

    setFriends(friendsList : User[]) {
      this.user.friends = friendsList;
    },
    setToken(token: string) {
        this.user.token = token;
    },
    setTwoFa(status : boolean) {
      this.user.twoFa = status
    },
    addWin() {
      this.user.win++;
    },

    addLose() {
        this.user.lose++;
      },

    async fetchFriends() {
        try {
            // console.log('request FriendsList : ' + this.user.id);
            const res = await GetFriendsList(this.user.id);
            if(res.status == 200)
            {
              this.setFriends(res.data);
              // console.log('친구목록 업데이트', this.user.friends);
            }
        } catch {
            console.error('Error Friends');
        }
    },
    async fetchBlocks() {
      try {
          const res = await GetBlocksList(this.user.id);
          if(res.status == 200)
          {
            this.user.blocks = res.data;
          }
      } catch {
          console.error('Error Friends');
      }
  },
    setDashBoard(res : any){
      // console.log("set Dashboard " , res);
      this.user.win = res.wins;
      this.user.lose = res.loses;
    },
    setGameHistory(res :any){
      // console.log("set history " , res);
      this.user.gameHistory = res;
    },

    restoreChannel(newchannels : any[]){
      // console.log ('SET restore Channel : ', newchannels);
      if(this.user.Channels.length === 0)
      {
        newchannels.forEach(data => {
          const newItem : Channel = {
            type: data.type,
            roomname: data.roomname,
            status: data.status,
            admin: data.admin,
            owner: data.owner,
            member: data.member,
            message: [],
            unread : 0
          };
          this.setChannel(newItem);
        });
      }
    },
    setChannel(channel : Channel) {
      channel.unread = 0;
      if (channel.type == 'msg')
      {
        const index = this.user.Channels.findIndex(item => item.type === 'msg');
        if (index !== -1) {
          this.user.Channels[index] = channel;
          // console.log("change channel");
        }
        else
        {
          this.user.Channels.unshift(channel);
          // console.log("push channel");
        }
      }
      else
      {
        let index = -1;
        let i = 0;
        while(i < this.user.Channels.length)
        {
          if(this.user.Channels[i].type == 'dm')
          {
              index = this.user.Channels[i].member.findIndex(item => item.id == channel.member.find(item => item.id != this.user.id)?.id);
              if(index != -1)
                break ;               
          }
          i++;
        }
        if(index != -1)
        {
          channel.message.unshift(...this.user.Channels[i].message);
          this.user.Channels.splice(i, 1);
        }
        this.user.Channels.unshift(channel);
      }
    },
    updateMember(roomName : string){
      PostUpdateMembers(roomName, this.user.id).then(response =>  {
        const index = this.user.Channels.findIndex(item => item.roomname === roomName);
        if(index != -1)
        {
          this.user.Channels[index].member = response?.data;
        }
      }); 

    },

    async updateChat(msg : any) {
      if(msg.type != 'not' && this.user.blocks.findIndex(item => item.username === msg.username) != -1)
      {
        console.log('차단된 유저의 메세지 입니다.')
        return ; 
      }
      if(msg.type === 'msg')
      {
        const index = this.user.Channels.findIndex(item => item.type === 'msg');
        if (index !== -1) {
          const newmsg : Msg = { type : 'message', id: msg.userid, name : msg.username, avatar : msg.avatar, message: msg.msg};
          this.user.Channels[index].message.push(newmsg);
          const [channel] = this.user.Channels.splice(index, 1);
          channel.unread++;
          this.user.Channels.unshift(channel);
        }
        else
          console.log('없는 방에 메세지요청');
      }
      else if(msg.type === 'dm'){
            await this.fetchFriends();
            if (msg.username !=  this.user.name && this.user.friends.findIndex(item => item.username === msg.username) == -1)
            {
              console.log(msg.username, "친구아님");
              return;
            }
            const index2 = this.user.Channels.findIndex(item => item.roomname === msg.roomname);
            if (index2 !== -1) {
              const newmsg : Msg = { type : 'message',id: msg.userid, name : msg.username, avatar : msg.avatar, message: msg.msg};
              this.user.Channels[index2].message.push(newmsg);
              const [channel] = this.user.Channels.splice(index2, 1);
              channel.unread++;
              this.user.Channels.unshift(channel);
            }
            else {
              const newmsg2 : Msg = { type : 'message', id: msg.userid, name : msg.username, avatar : msg.avatar, message: msg.msg};
              let index = -1;
              let msgs : Msg[] = [];
              for(let i = 0; i < this.user.Channels.length; i++)
              {
                if(this.user.Channels[i].type == 'dm')
                {
                    index = this.user.Channels[i].member.findIndex(item => item.id == msg.userid);
                    if(index != -1)
                      break ;               
                }
              }
              if(index != -1)
              {
                msgs = this.user.Channels[index].message;
                this.user.Channels.splice(index, 1);
              }
              const newChannel : Channel = {
                type: 'dm',
                roomname: msg.roomname,
                status: 'public',
                admin: [],
                owner : '',
                member: [{id : msg.userid, status : '' , username : msg.username, avatar : msg.avatar}],
                message: msgs,
                unread: 0
              }
              newChannel.message.push(newmsg2);
              newChannel.unread++;
              this.user.Channels.unshift(newChannel);
            }
      }
      else if(msg.type === 'not'){
            const index = this.user.Channels.findIndex(item => item.roomname === msg.roomname);
            if (index !== -1) {
              if(msg.expel == true && msg.userid === this.user.id)
              {
                this.user.Channels.splice(index, 1);
                usePopupStore().setNotiBell({type : 'not', userid : this.user.id, username : `${this.user.name}님은 ${msg.roomname}방에서 강퇴당하셨습니다.`});              }
              else{
                const newmsg : Msg = { type : 'notification',id: msg.userid, name : msg.username, avatar : msg.avatar, message: msg.msg};
                this.user.Channels[index].message.push(newmsg);
                const [channel] = this.user.Channels.splice(index, 1);
                channel.unread++;
                this.user.Channels.unshift(channel);
                this.updateMember(msg.roomname);
              }
            }
        }
      },

      setReadChannel(name : string) {
        const index = this.user.Channels.findIndex(item => item.roomname === name);
        if (index != -1)
          this.user.Channels[index].unread = 0;
      },

      async exitRoom(name : string) {
        const index = this.user.Channels.findIndex(item => item.roomname === name);
        this.user.Channels.splice(index, 1);
      },

      setRoomAdmin(newAdmin : string[]) {
       const index = this.user.Channels.findIndex(item => item.type === 'msg');
       if (index != -1)
        this.user.Channels[index].admin = newAdmin;
      },

      updateAdmin(msg : any) {
        const index = this.user.Channels.findIndex(item => item.roomname === msg.roomname);
        if (index != -1)
        {
          this.user.Channels[index].admin = msg.admin;
          this.user.Channels[index].owner = msg.owner;
        }
      },

      deleteDMChannel(username : string) {
        const index = this.user.Channels.findIndex(channel => channel.type === 'dm' && channel.roomname.includes(username));
        if(index != -1)
          this.user.Channels.splice(index, 1);
      }
  },
  
})