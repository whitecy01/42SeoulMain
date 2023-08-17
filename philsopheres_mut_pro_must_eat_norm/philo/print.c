/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:40:59 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/16 18:22:52 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *tmp)
{
	write(2, tmp, str_length(tmp));
	return ;
}

int	printf_time_number(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->info->print));
	if (check_death(philo))
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (1);
	}
	printf("%ld %d %s\n", time_init() - philo->info->start_time, \
		philo->philo_name, msg);
	pthread_mutex_unlock(&(philo->info->print));
	return (0);
}

// void    free_philo(t_info *info)
// {
//     int i;

//     i = 0;
//     while (i < info->philo_number)
//     {
//         free(&(info->philo[i]));
//         i++;
//     }
//     i = 0;
// 	while (i < info->philo_number)
// 	{
// 		free(&(info->fork_m[i]));
// 		i++;
// 	}
// }