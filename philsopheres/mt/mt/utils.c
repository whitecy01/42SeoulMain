/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:37:46 by mtak              #+#    #+#             */
/*   Updated: 2021/07/24 00:38:06 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	num;

	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	num = 0;
	while (48 <= *str && *str <= 57)
	{
		num *= 10;
		num = num + *str - 48;
		str++;
	}
	if (num > LLONG_MAX - 1 && sign == 1)
		return (-1);
	if (num > LLONG_MAX && sign == -1)
		return (0);
	return (sign * num);
}

void	sleep_ms(long time)
{
	long	start_time;
	long	present_time;

	start_time = get_time();
	while (1)
	{
		present_time = get_time();
		if (present_time - start_time > time)
			break ;
		usleep(500);
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	print_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->to_set);
	pthread_mutex_lock(philo->to_get);
	if (g_overeating_philo < philo->info.philo_num
		&& g_dead_philo == 0)
	{
		pthread_mutex_unlock(philo->to_get);
		printf("%ldms %d%s", get_time() - philo->start_time, philo->idx, str);
		pthread_mutex_unlock(philo->to_set);
		return ;
	}
	pthread_mutex_unlock(philo->to_set);
	pthread_mutex_unlock(philo->to_get);
}
