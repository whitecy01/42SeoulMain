/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee   <minslee@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:22:04 by minslee           #+#    #+#             */
/*   Updated: 2022/09/21 18:59:06 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define FAIL		(0)
# define SUCCESS	(1)

typedef struct s_arg
{
	int						total_philo;
	int						die_time;
	int						eat;
	int						sleep;
	int						must_eat;
	long int				start_t;
	pthread_mutex_t			status_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_p_finish;
	int						stop;
}							t_arg;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_arg					*pa;
	long int				start_eat_ms;
	unsigned int			eat_num;
	int						finish;
}							t_philo;

typedef struct s_table
{
	t_philo					*philo;
	t_arg					a;
}							t_table;

int				parse_args(int argc, char **argv, t_table *table);
int				initialize(t_table *table);
int				ft_exit(char *str);
void			write_status(char *str, t_philo *ph);
long int		actual_time(void);
void			ft_putstr_fd(char *s, int fd);
void			ft_usleep(long int time_in_ms);
int				threading(t_table *table);
void			activity(t_philo *ph);
int				check_death(t_philo *ph, int i);
int				ft_strlen(char *str);

#endif
