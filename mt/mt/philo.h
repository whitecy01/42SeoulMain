/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:23:16 by mtak              #+#    #+#             */
/*   Updated: 2021/07/24 00:28:49 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

# define STARVED	0
# define FULL		1
# define DEAD		2

int					g_overeating_philo;
int					g_dead_philo;

typedef struct s_info
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_num;
	pthread_mutex_t	to_set;
	pthread_mutex_t	to_get;
	pthread_mutex_t	*forks;
	int				max_idx;
}					t_info;

typedef struct s_philo
{
	int				idx;
	pthread_t		thread;
	t_info			info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*to_set;
	pthread_mutex_t	*to_get;
	pthread_mutex_t	to_eat;
	long			start_time;
	long			last_meal_time;
	int				eat_count;
	int				status;
}					t_philo;

int					is_str_num(char *str);
int					init_info(t_info *info, int argc, char **argv);
int					init_mutexes(t_info *info);
t_philo				*init_philos(t_info *info);
void				free_machine(t_philo *philo,
						pthread_mutex_t *forks, pthread_mutex_t *to_set,
						pthread_mutex_t *to_get);
int					check_death(t_philo *philo);
int					check_full(t_philo *philo);
void				*check_status(void *p);
void				sleeping(t_philo *p);
void				eat(t_philo *philo);
void				*routine(void *p);
void				action(t_info i, t_philo *p);
int					ft_atoi(const char *nptr);
void				sleep_ms(long time);
long				get_time(void);
void				print_msg(char *str, t_philo *philo);

#endif
