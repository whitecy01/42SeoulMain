import { defineStore } from 'pinia'
import { useUserStore } from './user';
import { usePopupStore } from './status';
import { Socket } from 'socket.io-client';
import io from 'socket.io-client';

let socket : Socket | null = null;

export const useSocketStore =  defineStore('socket', {
    persist: {
        enabled: true,
        strategies: [{ storage: sessionStorage }],
      },
    state: () => ({
        isConnected: false,
        username: '',
    }),

  actions: {
    setsocket (){
        if(!socket)
        {
            socket = io(`${process.env.VUE_APP_SERVERURL}${process.env.VUE_APP_SOCKETPORT}`, { query: {
                userid: useUserStore().user.id,
                token: useUserStore().user.token
              },
            });
            this.isConnected = true;
        }
        window.addEventListener('beforeunload', () => {
            this.disconnectSocket();
        });
    },
    disconnectSocket() {
        if (socket) {
            socket.disconnect();
            socket = null;
            this.isConnected = false;
        }
    },
    socketReset() {
        this.disconnectSocket();
        this.isConnected = false;
        this.username = '';
    },
    socketOnMsg() {
        socket?.on('getmessage', (msg : any) => {
            useUserStore().updateChat( msg);
          });
    },

    socketOnNotification() {
        socket?.on('notification', (msg : {
            type : 'friend' | 'game',
            userid : number,
            username : string,  
            }) => {

           if (msg.type === 'friend')
             usePopupStore().setNotiBell(msg);
            else if (msg.type === 'game')
            {
                usePopupStore().setNotiBell(msg); 
            }
          });
    },
    socketOnChangeAdmin() {
        socket?.on('changeadmin', (msg : {
            roomname : string,  
            admin: string[],
            owner: string
            }) => {
            useUserStore().updateAdmin(msg);
          });

    },
    socketOnFetchFriend(){
        socket?.on('fetchfriend', (result : number) => {
            useUserStore().fetchFriends()

          });
    },
    //게임소켓
    socketOnGameUpdate(){
        socket?.on('updateGame', (res : any) => {
            usePopupStore().setGameUpdate(res);
        })
    },
    socketOffGameUpdate(){
        socket?.off('updateGame');
    },
    socketOnPlayGame(){
        socket?.on('setGame', (res : any) => {
            usePopupStore().setGame({
                roomNum : res.roomNum,
                team : res.team,
                userId : res.userId
            })
            usePopupStore().setGameStatus('play');
        })
    },
    socketOffPlayGame(){
        socket?.off('setGame');
    },
    socketOnEndGame(){
        socket?.on('endGame', (res : any) => {
            usePopupStore().setGameUpdate(res);
            usePopupStore().setGameWinner(res.winner);
            usePopupStore().setGameStatus('end');
            const sendObj = {
                userId : useUserStore().user.id,
                roomNum : usePopupStore().game.roomNum,
                team : usePopupStore().game.team,
                winner : res.winner,
            }
            socket?.emit('saveGame', sendObj);
        })
    },
    socketOffEndGame(){
        socket?.off('endGame');
    },
    socketOnTimeout(){
        socket?.on('timeOutGame', (res : any) => {
            usePopupStore().setGameStatus('timeOut');
        })
    },
    socketOffTimeout(){
        socket?.off('timeOutGame');
    },
    matchGame(){
        const sendObj = {
            userId : useUserStore().user.id,
        }
        socket?.emit('readyGame', sendObj);
    },
    sendGameStatus() {
        const sendObj = {
            roomNum : usePopupStore().game.roomNum,
            team : usePopupStore().game.team,
            y: usePopupStore().getGameMyPosition
        }
        socket?.emit('playGame', sendObj);
    },
    cancelGame() {
        console.log('cancelGame');
        socket?.emit('cancelGame');
    },

    //
    connectSocket(mtype : string, from : number, to : string ) : Promise<string> {
        return new Promise((resolve) => {
        const sendObj = {
            type: mtype,
            userfrom: from,
            userto: to
        };
    
        socket?.emit('connectsocket', sendObj, (response: any) => {
            resolve(response);
        });
        });
    },
    addFriend( me : number, friend : number){
        const sendObj = {
            userto : me,
            userfrom : friend
        }
        socket?.emit('addfriend', sendObj);
    },
    sendMessage(sendObj : {type : "msg" | "dm" | "not" , roomname: string, userid: number, msg: string}) {
        socket?.emit('sendmessage', sendObj, (response : any) => {
            if (!response.mute)
            {
                useUserStore().updateChat(
                {
                    type: sendObj.type,
                    userid: useUserStore().user.id,
                    roomname: sendObj.roomname,
                    username: useUserStore().user.name,
                    avatar: useUserStore().user.avatar,
                    msg : sendObj.msg
                })    
            }
            else{
                useUserStore().updateChat(
                    {
                    type: 'not',
                    roomname: sendObj.roomname,
                    id : 0,
                    username: '',
                    avatar: '',
                    msg : '당신은 채팅금지 상태입니다.'
                    })  
            }
        });
    },

    enterRoom(mtype : "msg" | "dm", mroomname: string) {
        const sendObj = {
            type : mtype,
            roomname : mroomname,
            userid : useUserStore().user.id,
        }
        if(mtype === 'msg' && useUserStore().user.Channels.findIndex(item => item.roomname === mroomname) != -1)
         {
            console.log('같은 방');
            return ;
         }
        if(mtype === 'msg' && useUserStore().user.Channels.findIndex(item => item.type === 'msg') != -1)
        {
            console.log('기존exit');
            this.exitRoom();
        }
        socket?.emit('enterroom', sendObj, (response : any) => {

            useUserStore().setChannel({
                type : response.type,
                roomname: response.roomname,
                status: response.status,
                admin: response.admin,
                owner: response.owner,
                member: response.members,
                message: [],
                unread: 0});
            if(response.type == 'msg')
                useUserStore().updateMember(response.roomname);
        });
    },

    exitRoom() {
        const channel = useUserStore().getChannelsList;
        const index = channel.findIndex(item => item.type == 'msg');
        if(index != -1)
        {
            const sendObj = {
                    type : channel[index].type,
                    roomname : channel[index].roomname,
                    userid : useUserStore().user.id,
            }
            socket?.emit('exitroom', sendObj);
            useUserStore().exitRoom(channel[index].roomname)
        }
    },

    delegateAdmin(roomName : string, userId : number) {
        socket?.emit('delegateadmin', {
            roomname: roomName,
            userid: userId
        });

    },

    expelUser(type : string, userId : number, roomName : string) {
        const sendObj = {
            type : type,
            roomname : roomName,
            userid : userId
        }
        socket?.emit('expeluser', sendObj);
    },

    restoreChannel() {
        socket?.emit('restoreChannel', useUserStore().user.id, (response : any) => {
            useUserStore().restoreChannel(response)
        });
    }
  }
})