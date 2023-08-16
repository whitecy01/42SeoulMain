/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee   <minslee@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:26:28 by minslee           #+#    #+#             */
/*   Updated: 2022/09/21 19:03:08 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

int	is_all_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (ft_strlen(argv[i]) > 10)
		return (FAIL);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	if ((argc == 5 || argc == 6) && is_all_digit(argv))
	{
		table->a.total_philo = ft_atoi(argv[1]);
		table->a.die_time = ft_atoi(argv[2]);
		table->a.eat = ft_atoi(argv[3]);
		table->a.sleep = ft_atoi(argv[4]);
		table->a.must_eat = -1;
		if (argc == 6)
			table->a.must_eat = ft_atoi(argv[5]);
		if (table->a.total_philo <= 0 || table->a.die_time <= 0 \
			|| table->a.eat <= 0 || table->a.sleep <= 0)
			return (FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}

void	init_mutex(t_table *table)
{
	pthread_mutex_init(&table->a.status_mutex, NULL);
	pthread_mutex_init(&table->a.dead, NULL);
	pthread_mutex_init(&table->a.time_eat, NULL);
	pthread_mutex_init(&table->a.finish, NULL);
}

int	initialize(t_table *table)
{
	int	i;

	i = 0;
	table->a.start_t = actual_time();
	table->a.stop = 0;
	table->a.nb_p_finish = 0;
	init_mutex(table);
	while (i < table->a.total_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].start_eat_ms = table->a.start_t;
		table->philo[i].eat_num = 0;
		table->philo[i].finish = 0;
		table->philo[i].right_fork = NULL;
		pthread_mutex_init(&table->philo[i].left_fork, NULL);
		if (table->a.total_philo == 1)
			return (SUCCESS);
		if (i == table->a.total_philo - 1)
			table->philo[i].right_fork = &table->philo[0].left_fork;
		else
			table->philo[i].right_fork = &table->philo[i + 1].left_fork;
		i++;
	}
	return (SUCCESS);
}
