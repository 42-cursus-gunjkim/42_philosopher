/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:34:47 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 00:33:55 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MILLI 1000
# define NO_FULL_CNT -1

enum e_fork_status
{
	PICKABLE,
	PICKED
};

enum e_hand
{
	LEFT,
	RIGHT
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_result
{
	FAIL,
	SUCCESS
};

enum e_philo_status
{
	PICK,
	EAT,
	SLEEP,
	THINK,
	DEATH
};

typedef struct s_fork
{
	int					status;
	pthread_mutex_t		fork_mtx;
}	t_fork;

typedef struct s_com
{
	pthread_mutex_t	log_mtx;
	pthread_mutex_t	ttd_mtx;
	struct timeval	start_time;
	int				ttd;
	int				philo_cnt;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				full_cnt;
	int				all_done;
}	t_com;

typedef struct s_philo
{
	pthread_mutex_t	last_eat_mtx;
	pthread_mutex_t	full_mtx;
	pthread_t		thread;
	int				id;
	int				total_eat;
	int				full;
	long			last_eat;
	t_com			*common;
	t_fork			*left;
	t_fork			*right;
}	t_philo;

int		parse_arg(int argc, char *argv[], t_com *common);
void	print_log(t_philo *philo, int status);
long	get_time(struct timeval *start_time);
void	put_forks(t_philo *philo);
void	take_forks(t_philo *philo, int hand);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	spend_time(long time, t_philo *philo);
int		spaghetti_time(t_com *common, t_philo *philos);
long	s_check_long(pthread_mutex_t *mtx, long *target, long value);
void	s_set_long(pthread_mutex_t *mtx, long *target, long value);
int		s_check_int(pthread_mutex_t *mtx, int *target, int value);
void	s_set_int(pthread_mutex_t *mtx, int *target, int value);
void	s_mul(pthread_mutex_t *mtx, int *target, int *result);

#endif