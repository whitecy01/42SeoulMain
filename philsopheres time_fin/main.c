/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/15 18:17:28 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int	lower_bound(int time, int num)
// {
// 	if (num % 2 == 1)
// 	{
// 		if (time < 600)
// 			time = 600;
// 	}
// 	else
// 	{
// 		if (time < 70)
// 			time = 70;
// 	}
// 	return (time);
// }

// int	ft_usleep(int goal_time, int num) // goal_time 만큼 시간을 usleep하고 나오는 함수
// {
// 	int		must_spend_time;
// 	int		start_time;
// 	int		end_time;
// 	struct timeval start;
// 	struct timeval end;

// 	goal_time *= 1000;
// 	gettimeofday(&start, NULL);
// 	gettimeofday(&end, NULL);
// 	start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
// 	end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
	
// 	// 123456777
// 	// 12345678
// 	// 3
// 	// while(1)
// 	// {
// 	// start_time 갱신 X
// 	// end_time은 계속 get_time()해서 구한 값을
// 	// if(!get_time() - start_time < goal_time)
// 	// 	break;
// 	// usleep(1000);
// 	// }
// 	while (goal_time >= end_time - start_time)
// 	{
// 		end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
// 		// 만일 지금 현재 end-start 시간이 goal_time 보다 작으며
// 		// 400 -> end-start 10 => 390 => 이때는 usleep을 을 건다?
// 		// 400 -> end-start 350 => 50 => 이떄는 uslepp을 40000을 주기
// 		// 400              395 => 5 =>                4000
// 		must_spend_time = (goal_time - (end_time - start_time)) * 3 / 4;
		
// 		must_spend_time = lower_bound(must_spend_time, num);
// 		usleep(must_spend_time);
// 		gettimeofday(&end, NULL);
// 	}
// 	return (0);
// }

void	print_error(char *tmp)
{
	write(2, tmp, str_length(tmp));
	return ;
}

long int	time_init(void)
{
	long int			time;
	struct timeval		current_time;


	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		print_error("Gettimeofday returned\n");
	//printf("current_time.tv_sec : %ld current_time.tv_usec : %d\n",current_time.tv_sec , current_time.tv_usec);
	//printf("current_time.tv_sec  * 1000 : %ld current_time.tv_usec / 1000 : %d\n",current_time.tv_sec * 1000 , current_time.tv_usec / 1000);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	//printf("time : %ld\n", time);
	return (time);
}

// static unsigned int	ft_get_time(int init)
// {
// 	static unsigned int	start_time;
// 	struct timeval		t;

// 	gettimeofday(&t);
// 	if (init)
// 	{
// 		start_time = t.tv_usec / 1000 + t.tv_sec * 1000;
// 		return (0);
// 	}
// 	return (t.tv_usec / 1000 + t.tv_sec * 1000 - start_time);
// }

void	ft_pass_time(long int time_to_eat, t_info *info)
{
	long int	start;
	long int	now;

	start = time_init();
	//pthread_mutex_lock(&(info->death_m));
	while (!(info->death_flag))
	{
		now = time_init();
		if ((now - start) >= time_to_eat)
			break ;
		usleep(500);
		//pthread_mutex_unlock(&(info->death_m));
	}
	//pthread_mutex_unlock(&(info->death_m));
}

int	printf_time_number(t_philo *philo, char *msg)
{
	//long int now;

	//= time_init();
	pthread_mutex_lock(&(philo->info->print));
	if (philo->info->death_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (1);
	}
	printf("%ld %d %s\n", time_init() - philo->info->start_time , philo->philo_name, msg);
	pthread_mutex_unlock(&(philo->info->print));
	return (0);
}

int	thread_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork_m[philo->fork_left]));
	if (printf_time_number(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_left]));
		return (1);
	}
	pthread_mutex_lock(&(philo->info->fork_m[philo->fork_right]));
	printf_time_number(philo, "has taken a fork");
	printf_time_number(philo, "is eating");
	philo->eat = philo->eat + 1;
	philo->thread_time = time_init();
	//죽음 체크 usleep 함수 == eat time만큼 sleep 시켜주는 함수만들기
	//ft_usleep(philo->info->time_to_eat, philo->philo_name);
	ft_pass_time(philo->info->time_to_eat, philo->info);
	pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_right]));
	pthread_mutex_unlock(&(philo->info->fork_m[philo->fork_left]));
	return (0);
}

void	*action_thread(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
	
	if (philo->philo_name % 2 == 0)
		usleep(1000);
	//usleep(100 * philo->philo_name);
	//printf("action_thread_philo->name : %d\n", philo->philo_name);
	//printf("philo->name : %d\n", philo->philo_name);
	//eat, think, sleep
	pthread_mutex_lock(&(philo->info->death_m));
	while(!(philo->info->death_flag))
	{
		pthread_mutex_unlock(&(philo->info->death_m));
		//먹는 거 (집는 거, 내리는 거, 출력하는 것)
		if (thread_eat(philo) == 1)
		{
			pthread_mutex_unlock(&(philo->info->death_m));
			return (0);
		}
		//자는 거
		printf_time_number(philo, "is sleeping");
		ft_pass_time(philo->info->time_to_eat, philo->info);
		//생각하기
		printf_time_number(philo, "is thinking");
		//philo->thread_time = time_init();
		pthread_mutex_lock(&(philo->info->death_m));
	}
	pthread_mutex_unlock(&(philo->info->death_m));

	return ((void *)0);
}

int	check_death(t_philo *philo)
{
	int result;

	pthread_mutex_lock(&(philo->info->death_m));
	result = philo->info->death_flag;
	pthread_mutex_unlock(&(philo->info->death_m));
	return (result);
}

int	check_time(t_philo *philo)
{
	int result;

	pthread_mutex_lock(&(philo->info->death_m));
	result = philo->info->time_to_die;
	pthread_mutex_unlock(&(philo->info->death_m));
	return (result);
}

void	ft_philo_check_finish(t_philo *philo)
{
	int			i;
	long int	now;


	if (philo->info->must_eat > 1)
	{
			// if ((philo->info->must_eat != 0) && (philo->info->philo_number == philo->info->))
			// {
			// 	philo->info->death_flag = 1;
			// 	break ;
			// }
	}
	else
	{
		//pthread_mutex_lock(&(philo->info->death_m));
		while (!(philo->info->death_flag))
		{
			i = 0;
			while (i < philo->info->philo_number)
			{
				now = time_init();
				if ((now - philo[i].thread_time) > philo->info->time_to_die)
				{
					printf_time_number(philo, "died");
					philo->info->death_flag = 1;
					break ;
				}
				i++;
			}
		}
	}
}

int	ft_philo_start(t_info *info)
{
	int i = 0;

	info->start_time = time_init();
	while (i < info->philo_number)
	{
		info->philo[i].thread_time = time_init();
		pthread_create(&(info->philo[i].thread), NULL, action_thread, &(info->philo[i]));
		i++;
	}
	ft_philo_check_finish(info->philo);
	i = 0;
	while (i < info->philo_number)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	//free
	//죽는 거 
	return (0);
}



int	main(int argc, char **argv)
{
	t_info info;
	//argc가 5와 6 밖에 있을 때 error
	if (!(argc >= 5 && argc <= 6))
	{
		print_error("Wrong argc\n");
		return (1);
	}
	//argv 인자값 atoi처리
	if (init(&info, argv, argc))
	{
		print_error("Wrong argv\n");
		return (1);
	}
	//필로 1명일때
	//1명일 때는 포크가 하나 
	//fork[i], fork [(i + 1) % n] -> 2개의 포크(오른쪽, 왼쪽)가 같은 거 인지
	
	//뮤텍스 init
	//쓰레드 액션
	ft_philo_start(&info);
	
}

