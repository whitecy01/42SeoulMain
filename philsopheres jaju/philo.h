/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:31:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/13 19:12:42 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define SUCCESS	1
# define FAIL		0

typedef struct s_philo
{
	int			philo_name;
	int			fork_left;
	int			fork_right;
	long int	thread_time;
	int			eat;
	pthread_t	thread;
	struct s_info		*info;
}	t_philo;


typedef struct s_info
{
	//argv 인자
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	//먹는 시간 초과
	int	death_flag;
	//시작 시간
	long int start_time;
	//mutex
	//1. 먹는 시간
	pthread_mutex_t count_eat;
	//2. 출력하는 거
	pthread_mutex_t print;
	//3. 죽었는지 확인하는 뮤텍스
	pthread_mutex_t death_m;
	//4. 포크를 들었는지 안들었는제
	pthread_mutex_t *fork_m;
	
	
	//쓰레드 하나 정보 입력
	
	t_philo			*philo;
}t_info;

int	str_length(char *tmp);
int	init_mutex(t_info *info);
int	init(t_info *info, char **argv, int argc);

long	atoi_while(char *str);
long int	time_init(void);
void	print_error(char *tmp);

#endif