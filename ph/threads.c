/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee   <minslee@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:26:35 by minslee           #+#    #+#             */
/*   Updated: 2022/09/21 19:02:01 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->pa->die_time + philo->pa->total_philo);
	pthread_mutex_lock(&philo->pa->time_eat);
	pthread_mutex_lock(&philo->pa->finish);
	if (!check_death(philo, 0) && !philo->finish && \
		((actual_time() - philo->start_eat_ms) >= (long)(philo->pa->die_time)))
	{
		pthread_mutex_unlock(&philo->pa->time_eat);
		pthread_mutex_unlock(&philo->pa->finish);
		pthread_mutex_lock(&philo->pa->status_mutex);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->pa->status_mutex);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->pa->time_eat);
	pthread_mutex_unlock(&philo->pa->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->pa->eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, data);
		activity(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->eat_num == philo->pa->must_eat)
		{
			pthread_mutex_lock(&philo->pa->finish);
			philo->finish = 1;
			philo->pa->nb_p_finish++;
			if (philo->pa->nb_p_finish == philo->pa->total_philo)
			{
				pthread_mutex_unlock(&philo->pa->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->pa->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	threading(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->a.total_philo)
	{
		table->philo[i].pa = &table->a;
		if (pthread_create(&table->philo[i].thread_id, NULL, thread, \
			&table->philo[i]) != 0)
			return (!printf("0 Not Returned\n"));
		i++;
	}
	return (SUCCESS);
}
