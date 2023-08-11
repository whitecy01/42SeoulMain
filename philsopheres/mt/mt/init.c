/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:25:02 by mtak              #+#    #+#             */
/*   Updated: 2021/07/24 00:31:54 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_str_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	init_info(t_info *info, int ag, char **av)
{
	int	i;

	if (ag != 5 && ag != 6)
		return (0);
	i = 1;
	while (i < ag)
	{
		if (!is_str_num(av[i]))
			return (0);
		i++;
	}
	info->philo_num = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->must_eat_num = -1;
	if (ag == 6)
		info->must_eat_num = ft_atoi(av[5]);
	info->max_idx = info->philo_num - 1;
	return (1);
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (info->forks == NULL)
		return (0);
	while (++i < info->philo_num)
		pthread_mutex_init(&(info->forks[i]), NULL);
	pthread_mutex_init(&info->to_set, NULL);
	pthread_mutex_init(&info->to_get, NULL);
	return (1);
}

t_philo	*init_philos(t_info *info)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < info->philo_num)
	{
		philos[i].idx = i;
		philos[i].info = *info;
		philos[i].left_fork = &info->forks[i];
		if (i == info->philo_num - 1)
			philos[i].right_fork = &info->forks[0];
		else
			philos[i].right_fork = &info->forks[i + 1];
		philos[i].to_set = &info->to_set;
		philos[i].to_get = &info->to_get;
		pthread_mutex_init(&philos[i].to_eat, NULL);
		philos[i].start_time = get_time();
		philos[i].last_meal_time = get_time();
		philos[i].eat_count = 0;
		philos[i].status = STARVED;
	}
	return (philos);
}
