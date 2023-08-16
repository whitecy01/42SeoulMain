/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:29:21 by mtak              #+#    #+#             */
/*   Updated: 2021/07/24 00:25:54 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	print_msg(" is sleeping\n", philo);
	sleep_ms(philo->info.time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(" has taken a fork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	print_msg(" has taken a fork\n", philo);
	print_msg(" is eating\n", philo);
	pthread_mutex_lock(&philo->to_eat);
	philo->last_meal_time = get_time();
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->to_eat);
	sleep_ms(philo->info.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *p)
{
	pthread_t	monitor;
	t_philo		*philo;

	philo = (t_philo *)p;
	if (philo->idx % 2)
		sleep_ms(20);
	pthread_create(&monitor, NULL, check_status, p);
	pthread_mutex_lock(philo->to_get);
	while (g_overeating_philo < philo->info.philo_num
		&& g_dead_philo == 0)
	{
		pthread_mutex_unlock(philo->to_get);
		eat(philo);
		sleeping(philo);
		print_msg(" is thinking\n", philo);
		pthread_mutex_lock(philo->to_get);
	}
	pthread_mutex_unlock(philo->to_get);
	pthread_detach(monitor);
	return (NULL);
}

void	action(t_info info, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < info.philo_num)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	}
	i = -1;
	while (++i < info.philo_num)
	{
		pthread_join(philos[i].thread, NULL);
	}
}
