/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:14:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 00:07:42 by gunjkim          ###   ########.fr       */
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

typedef struct s_common
{
	pthread_mutex_t	log;
	struct timeval	start_time;
	struct timeval	cur;
	long long		time_die;
	long long		time_eat;
	long long		time_think;
	long long		time_sleep;
	int				full;
}	t_common;

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
	t_common		*common;
	struct timeval	last_eat;
	t_fork			*left;
	t_fork			*right;
	pthread_mutex_t	ttd_lock;
	pthread_mutex_t	info_lock;
}	t_info;

char	*ft_itoa(long long n);
int		parse_argv(int argc, char *argv[], t_common *common, int *philo_count);
int		spaghetti_time(pthread_t *philos, t_info *infos, int philo_count);
void	put_log_msg(int state, t_info *info);
long	diff_time(struct timeval *t1, struct timeval *t2);
void	grap_two_fork(t_info *info);
void	eat_spaghetti(t_info *info);
void	philo_sleep_finally_think(t_info *info);
void	get_time(long long time);

#endif
