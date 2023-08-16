/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:37:29 by mtak              #+#    #+#             */
/*   Updated: 2021/07/24 00:41:48 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->to_eat);
	if (now - philo->last_meal_time > philo->info.time_to_die)
	{
		pthread_mutex_unlock(&philo->to_eat);
		print_msg(" died\n", philo);
		philo->status = DEAD;
		pthread_mutex_lock(philo->to_get);
		g_dead_philo += 1;
		if (philo->info.max_idx == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
		}
		pthread_mutex_unlock(philo->to_get);
		return (1);
	}
	pthread_mutex_unlock(&philo->to_eat);
	return (0);
}

int	check_full(t_philo *philo)
{
	if (philo->info.must_eat_num != -1
		&& philo->eat_count >= philo->info.must_eat_num
		&& philo->status != FULL)
	{
		pthread_mutex_unlock(&philo->to_eat);
		philo->status = FULL;
		pthread_mutex_lock(philo->to_get);
		g_overeating_philo += 1;
		pthread_mutex_unlock(philo->to_get);
		return (1);
	}
	return (0);
}

void	*check_status(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->to_get);
	while (g_overeating_philo < philo->info.philo_num && !g_dead_philo)
	{
		pthread_mutex_unlock(philo->to_get);
		if (check_death(philo))
			break ;
		pthread_mutex_lock(&philo->to_eat);
		if (check_full(philo))
			continue ;
		pthread_mutex_unlock(&philo->to_eat);
		pthread_mutex_lock(philo->to_get);
	}
	pthread_mutex_unlock(philo->to_get);
	return (NULL);
}
