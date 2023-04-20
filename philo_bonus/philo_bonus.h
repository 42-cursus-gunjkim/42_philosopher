/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:40 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 05:35:28 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <signal.h>

# define MILLI 1000
# define NO_FULL_CNT -1

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

typedef struct s_com
{
	sem_t			*forks;
	sem_t			*log_sem;
	sem_t			*simul;
	struct timeval	start_time;
	int				philo_cnt;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				full_cnt;
	int				all_done;
}	t_com;

typedef struct s_philo
{
	int				id;
	int				total_eat;
	long			last_eat;
	t_com			*common;
}	t_philo;

int		spaghetti_time(t_com *common);
int		parse_arg(int argc, char *argv[], t_com *common);
void	spend_time(long time, t_philo *philo);
long	get_time(struct timeval *start_time);
void	print_log(t_philo *philo, int status);
void	*philo_monitor(void *arg);
void	philo_routine(t_philo *philo);

#endif