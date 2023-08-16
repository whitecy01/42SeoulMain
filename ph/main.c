/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee   <minslee@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:10:45 by minslee           #+#    #+#             */
/*   Updated: 2022/09/21 19:02:07 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_death2(t_table *table)
{
	pthread_mutex_lock(&table->a.dead);
	if (table->a.stop)
	{
		pthread_mutex_unlock(&table->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&table->a.dead);
	return (0);
}

void	stop(t_table *table)
{
	int	i;

	i = -1;
	while (!check_death2(table))
		ft_usleep(1);
	while (++i < table->a.total_philo)
		pthread_join(table->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&table->a.status_mutex);
	i = -1;
	while (++i < table->a.total_philo)
		pthread_mutex_destroy(&table->philo[i].left_fork);
	if (table->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", table->a.must_eat);
	free(table->philo);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (!(parse_args(argc, argv, &table)))
		return (!printf("Wrong Arguments!\n"));
	table.philo = malloc(sizeof(t_philo) * table.a.total_philo);
	if (!table.philo)
		return (!printf("NULL Returned\n"));
	if (!initialize(&table) || !threading(&table))
	{
		free(table.philo);
		return (0);
	}
	stop(&table);
}
