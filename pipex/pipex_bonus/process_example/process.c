/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:26:43 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/07 17:26:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int num_processes = 5;  // 생성할 자식 프로세스 수

    printf("부모 프로세스 시작 (PID: %d)\n", getpid());

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();  // 자식 프로세스 생성

        if (pid < 0) {
            fprintf(stderr, "자식 프로세스를 생성하는 데 실패했습니다.\n");
            return 1;
        } else if (pid == 0) {
            printf("자식 프로세스 생성 (PID: %d, 부모 PID: %d)\n", getpid(), getppid());
            sleep(1);  // 자식 프로세스 일시 정지
            exit(0);   // 자식 프로세스 종료
        }
    }

    // 부모 프로세스가 모든 자식 프로세스의 종료를 기다림
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("부모 프로세스 종료 (PID: %d)\n", getpid());

    return 0;
}
