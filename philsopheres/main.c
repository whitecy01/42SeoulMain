/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/12 20:39:22 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *tmp)
{
	write(2, tmp, str_length(tmp));
	return ;
}

long	atoi_while(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			result = (10 * result) + str[i] - '0';
		else
			print_error("Wrong number\n");
		i++;
	}
	if (i >= 11)
	{
		print_error("Wrong number\n");
		return (-1);
	}
	return (result);
}

int	parse_arg(t_info *info, char **argv, int argc)
{
	info->philo_number = atoi_while(argv[1]);
	info->time_to_die = atoi_while(argv[2]);
	info->time_to_eat = atoi_while(argv[3]);
	info->time_to_sleep = atoi_while(argv[4]);
	info->death_flag = 0;
	info->must_eat = -1;
	if (argc == 6)
		info->must_eat = atoi_while(argv[5]);
	if (info->philo_number <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
		if (info->must_eat <= 0)
			return (1);
	return (0);
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

int	init_mutex(t_info *info)
{
	info->start_time = time_init();
	pthread_mutex_init(&info->count_eat, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->death_m, NULL);
	pthread_mutex_init(&info->fork_m, NULL);
	info->philo = malloc(sizeof(t_philo) * info->philo_number);
	int i = 0;
	while (i < info->philo_number)
	{
		info->philo[i].philo_name = i + 1;
		info->philo[i].fork_left = (i + 1) % info->philo_number;
		info->philo[i].fork_right = i;
		info->philo[i].eat = 0;
		info->philo[i].thread_time = time_init();
		info->philo[i].info = info;
		//printf("philo_name : %d right : %d left : %d\n", info->philo[i].philo_name, info->philo[i].fork_right, info->philo[i].fork_left);
		//thread_time을 각각 넣어주면 되나,,?
		i++;
	}
	return (0);
}

void	printf_time_number(t_philo *philo, char *msg)
{
	long int now;

	now = time_init();
	pthread_mutex_lock(&(philo->info->print));
	printf("%ld %d %s \n", now - philo->thread_time, philo->philo_name, msg);
	pthread_mutex_unlock(&(philo->info->print));
}

int	lower_bound(int time, int num)
{
	if (num % 2 == 1)
	{
		if (time < 600)
			time = 600;
	}
	else
	{
		if (time < 70)
			time = 70;
	}
	return (time);
}

int	ft_usleep(int goal_time, int num)
{
	int		must_spend_time;
	int		start_time;
	int		end_time;
	struct timeval start;
	struct timeval end;

	goal_time *= 1000;
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
	while (goal_time >= end_time - start_time)
	{
		end_time = end.tv_sec * 1000 + end.tv_usec / 1000;
		must_spend_time = (goal_time - (end_time - start_time)) * 3 / 4;
		//must_spend_time = lower_bound(must_spend_time, num);
		usleep(must_spend_time);
		gettimeofday(&end, NULL);
	}
	return (0);
}

void	thread_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork_m));
	//pthread_mutex_lock(&(philo->fork_left));
	printf_time_number(philo, "has taken a fork");
	//죽음 체크 usleep 함수 만들기
	ft_usleep(philo->info->time_to_eat, philo->philo_name);
	//pthread_mutex_lock(&(philo->fork_right));
	//printf_time_number(philo, "has taken a fork");
	printf_time_number(philo, "is eating");
	pthread_mutex_unlock(&(philo->info->fork_m));
}

void	*action_thread(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
	
	if (philo->philo_name % 2 == 0)
		usleep(100 * philo->philo_name);
	printf("action_thread_philo->name : %d\n", philo->philo_name);
	//printf("philo->name : %d\n", philo->philo_name);
	//eat, think, sleep
	pthread_mutex_lock(&(philo->info->death_m));
	while(!(philo->info->death_flag))
	{
		pthread_mutex_unlock(&(philo->info->death_m));
		//먹는 거 (집는 거, 내리는 거, 출력하는 것)
		thread_eat(philo);
		
		//자는 거
		printf_time_number(philo, "is sleeping");
		//생각하기
		printf_time_number(philo, "is thinking");
		philo->thread_time = time_init();
		philo->eat = philo->eat + 1;
		pthread_mutex_lock(&(philo->info->death_m));
	}
	pthread_mutex_unlock(&(philo->info->death_m));

	return ((void *)0);
}

void	ft_philo_check_finish(t_philo *philo)
{
	int			i;
	long int	now;


	printf("DEBUG\n");
	if (philo->info->must_eat > 1)
	{

	}
	else
	{
		//while (!(philo->info->death_flag))
		//{
			// if ((philo->info->must_eat != 0) && (philo->info->philo_number == philo->info->//))
			// {
			// 	philo->info->death_flag = 1;
			// 	break ;
			// }
			i = 0;
			while (i < philo->info->philo_number)
			{
				now = time_init();
				if ((now - philo[i].thread_time) >= philo->info->time_to_die)
				{
					printf_time_number(philo, "is thinking");
					philo->info->death_flag = 1;
					break ;
				}
				i++;
			}
		//}
	}
}

int	ft_philo_start(t_info *info)
{
	int i = 0;

	while (i < info->philo_number)
	{
		pthread_create(&(info->philo[i].thread), NULL, action_thread, &(info->philo[i]));
		i++;
	}
	ft_philo_check_finish(info->philo);
	i = 0;
	while (i < info->philo_number)
		pthread_join(info->philo[i++].thread, NULL);
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
	if (parse_arg(&info, argv, argc))
	{
		print_error("Wrong argv\n");
		return (1);
	}
	//필로 1명일때
	//1명일 때는 포크가 하나 
	//fork[i], fork [(i + 1) % n] -> 2개의 포크(오른쪽, 왼쪽)가 같은 거 인지
	
	//뮤텍스 init
	init_mutex(&info);
	//쓰레드 액션
	ft_philo_start(&info);
	
}

