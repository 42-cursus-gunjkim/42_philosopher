/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:40 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 02:26:29 by gunjkim          ###   ########.fr       */
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
	sem_t			log_sem;
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
	pid_t			pid;
	int				id;
	int				total_eat;
	long			last_eat;
	t_com			*common;
}	t_philo;

int		spaghetti_time(sem_t *forks, t_com *common);
int		parse_arg(int argc, char *argv[], t_com *common);
void	spend_time(long time, t_philo *philo);
long	get_time(struct timeval *start_time);

#endif