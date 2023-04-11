/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:14:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 05:04:37 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>

# define MILLI 1000

# define NO_TIME_FULL -1
# define FORK 0
# define EAT 1
# define THINK 2
# define SLEEP 3
# define DEATH 4

typedef struct s_com
{
	pthread_mutex_t	log;
	struct timeval	start_time;
	struct timeval	cur;
	long long		time_die;
	long long		time_eat;
	long long		time_think;
	long long		time_sleep;
	int				full;
	int				all_full;
}	t_com;

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	key;
}	t_fork;

typedef struct s_info
{
	int				id;
	int				total;
	int				done;
	int				time_to_die;
	int				ing;
	t_com			*com;
	struct timeval	last;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t	ttd_lock;
	pthread_mutex_t	info_lock;
}	t_info;

int		parse_argv(int argc, char *argv[], t_com *com, int *philo_count);
void	spaghetti_time(pthread_t *philos, t_info *infos, int philo_count);
void	put_log_msg(int state, t_info *info);
long	diff_time(struct timeval *t1, struct timeval *t2);
void	philo_eat(t_info *info);
void	philo_sleep_think(t_info *info);
void	get_time(long long time);

#endif
