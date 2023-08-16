/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee   <minslee@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:26:16 by minslee           #+#    #+#             */
/*   Updated: 2022/09/21 19:01:42 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->status_mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->status_mutex);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->status_mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->status_mutex);
}

void	activity(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->pa->status_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->status_mutex);
	if (!ph->right_fork)
	{
		ft_usleep(ph->pa->die_time * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->pa->status_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->status_mutex);
	pthread_mutex_lock(&ph->pa->status_mutex);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->pa->time_eat);
	ph->start_eat_ms = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->status_mutex);
	ft_usleep(ph->pa->eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_think(ph);
}
