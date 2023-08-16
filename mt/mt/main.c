/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:23:00 by mtak              #+#    #+#             */
/*   Updated: 2021/07/21 00:54:07 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;

	g_dead_philo = 0;
	g_overeating_philo = 0;
	if (!(init_info(&info, argc, argv) && init_mutexes(&info)))
		return (1);
	philos = init_philos(&info);
	if (!philos)
		return (1);
	action(info, philos);
	free_machine(philos, info.forks, &info.to_set, &info.to_get);
	return (0);
}
