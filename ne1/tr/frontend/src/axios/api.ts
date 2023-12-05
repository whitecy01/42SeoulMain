import axios, { AxiosResponse } from 'axios';

const baseURL = process.env.VUE_APP_SERVERURL + process.env.VUE_APP_SERVERPORT;

export const apiClient = axios.create({
  baseURL: baseURL,
  timeout: 10000,
});

interface UserData {
    id: number;
    username: string;
    avatar: string;
}

interface User {
    id: number;
    status: string;
    username: string;
    avatar: string;
  }

  export const fa2post = async (newdata: any) => {
    try {
      const response: AxiosResponse<UserData> = await apiClient.post(`/auth/verify`,{
        data : newdata   
      });
      return response.data;
    } catch (error){
      void(error);
      throw(error);
    }
  };

export const fetchData = async (id: number) => {
  try {
    const response = await apiClient.get(`/user/${id}`);
    return response.data;
  } catch (error){
    void(error);
    throw(error);
  }
};

export const restoreRoom = async (id: number) => {
  try {
    const response = await apiClient.get(`/restoreRoom/${id}`);
    return response.data;
  } catch (error){
    void(error);
    throw(error);
  }
};

export const GetlogOut = async (id: number) => {
  try {
    const response = await apiClient.get(`/auth/42logout?id=${id}`);
    return response;
  } catch (error){
      void(error);
      throw(error);
  }
};
//setting
export const PostSetName = async (id: number, username :string) => {
    try { 
        const response = await apiClient.post(`/setUser/name/${id}`, {
            username : username
          })
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostSetAvatar = async (id: number, formData :FormData) => {
    try { 
        const response = await apiClient.post(`/profile/setUser/avatar/${id}`, formData,{
            headers: {'Content-Type': 'multipart/form-data',}
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };
//friend
export const GetFriendsList = async (id: number) => {
    try { 
        const response = await apiClient.get(`/friendsList/${id}`);
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const GetBlocksList = async (id: number) => {
    try { 
        const response = await apiClient.get(`/blockList/${id}`);
        return response;
    } catch (error){
        console.log('Blocklist API ERROR');
        throw(error);
    }
  };
  
  export const PostaddBlock =  async (id :number, username : string ) => {
    try { 
      const response = await apiClient.post(`/addBlock/${id}`, {
        username : username
      });
      return response;
  } catch (error){
      console.log('addBlock API ERROR');
      throw(error);
  }
  }

export const PostAddFriend = async (id: number, username :string) => {
    try { 
        const response = await apiClient.post(`/friendsList/${id}`,{
            username : username
        });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostConnectChat = async (id: number, friendId: number) => {
    try { 
        const response = await apiClient.post(`/chatFriend/${id}`, {
            userid: friendId
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostDeleteFreind = async (id: number, friendId: number) => {
    try { 
        const response = await apiClient.post(`/deleteFriend/${id}`, {
            userid: friendId
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostDeleteBlock = async (id: number, friendId: number) => {
    try { 
        const response = await apiClient.post(`/deleteBlock/${id}`, {
            userid: friendId
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  //channel
  export const GetChannelList = async (id :number) => {
    try { 
        const response = await apiClient.get(`/ChennelList/${id}`);
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostJoinChannel = async (id: number, channel: string, pw: string) => {
    try { 
        const response = await apiClient.post(`/enterRoom`, {
            userId : id,
            chennelName: channel,
            password : pw
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostCreateChannel = async (id: number, channel: string, pw: string, status: boolean) => {
    try { 
        const response = await apiClient.post(`/createRoom`, {
            userId :id,
            chennelName : channel,
            status : status,
            password : pw
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostExitChannel = async (id: number, channel: string) => {
    try { 
        const response = await apiClient.post(`/exitChannel`, {
            userId :id,
            chennelName : channel,
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostMuteUser = async (id : number, name: string, channel: string, userid :number) => {
    try { 
        const response = await apiClient.post(`/muteUser/${userid}`, {
            userTo : id,
            userName : name,
            chennelName : channel,
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostdelegateAdmin = async (id :number, name: string, channel: string) => {
    try { 
        const response = await apiClient.post(`/delegateAdmin`, {
            userId : id,
            userName : name,
            chennelName : channel,
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostInviteUser = async (name: string, user: string) => {
    try { 
        const response = await apiClient.post(`/inviteUser`, {
            roomName : name,
            userName : user,
          });
        return response;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostUpdateMembers = async (name : string, id : number) => {
    try {
      const response = await apiClient.post(`/updateMember/${id}`, {
        roomname :name
      });
      return response;
    }
    catch(error)
    {
      void(error);
    }
  }
  
  export const Post2FaSwich = async (type : string , id : number) => {
    try {
      const response = await apiClient.post('/auth/twoFactorAuthSwitch', {
        twoFactorAuth : type,
        userId : id
      });
      return response;
    }
    catch(error)
    {
      void(error);
    }
  }

  export const GetBanList = async (roomname: string, id :number): Promise<User[]> => {
    try { 
        const response: AxiosResponse<User[]> = await apiClient.get(`/banList/${roomname}/${id}`);
        return response.data;
    } catch (error){
        void(error);
        throw(error);
    }
  };

  export const PostCancelBan = async (roomname : string , id : number, userid :number) => {
    try {
      const response = await apiClient.post(`/cancelBan/${userid}`, {
        roomname : roomname,
        userTo : id
      });
      return response.data;
    }
    catch(error)
    {
      void(error);
    }
  }

  export const PostChangePassword = async (roomname : string, pw : string, id :number) => {
    try {
      const response = await apiClient.post(`/changePassword/${id}`, {
        roomname : roomname,
        password : pw
      });
      return response;
    }
    catch(error)
    {
      void(error);
    }
  }

  export const PostDashBoard = async (userName : string, id :number ) => {
    try {
      const response = await apiClient.post(`/profile/dashBoard/${id}`, {
        userName : userName
      });
      return response;
    }
    catch(error)
    {
      void(error);
    }
  }

  export const PostGameHistory = async (userid : number) => {
    try {
      const response = await apiClient.post(`/profile/dashBoard/history/${userid}`, {
        userId : userid
      });
      return response;
    }
    catch(error)
    {
      void(error);
    }
  }
  