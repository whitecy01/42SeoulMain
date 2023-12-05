import { HttpException, PipeTransform } from '@nestjs/common';

export class ProfileValidationPipe implements PipeTransform {
  transform(value: any) {
    if (!value.userName)
      throw new HttpException('유효한 유저 ID가 아닙니다.', 601, {
        cause: new Error('userID 입력값 없음'),
      });
    return value;
  }
}
