/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/11 21:05:35 by jaeyojun         ###   ########seoul.kr  */
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
	info->phio_number = atoi_while(argv[1]);
	info->time_to_die = atoi_while(argv[2]);
	info->time_to_eat = atoi_while(argv[3]);
	info->time_to_sleep = atoi_while(argv[4]);
	info->must_eat = -1;
	if (argc == 6)
		info->must_eat = atoi_while(argv[5]);
	if (info->phio_number <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
		if (info->must_eat <= 0)
			return (1);
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
	
	//쓰레드 액션
	
}

