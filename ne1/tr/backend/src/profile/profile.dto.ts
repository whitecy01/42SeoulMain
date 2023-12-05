import { User } from 'src/user/user.entity';

export interface ProfileDto {
  userName: string;
  newName: string;
}

export interface ProfileReturnDto {
  userName: string;
  imagePath: string;
}

export interface DashBoardDto {
  userId: User;
}
