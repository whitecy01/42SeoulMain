/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:28:31 by mtak              #+#    #+#             */
/*   Updated: 2021/07/20 21:16:15 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_machine(
	t_philo *philos,
	pthread_mutex_t *forks,
	pthread_mutex_t *to_set,
	pthread_mutex_t *to_get
)
{
	int	i;

	i = -1;
	while (++i < philos[0].info.philo_num)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].to_eat);
	}
	pthread_mutex_destroy(to_set);
	pthread_mutex_destroy(to_get);
	free(forks);
	free(philos);
}
