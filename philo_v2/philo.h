/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:34:47 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/13 15:52:24 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define MILLI 1000

enum e_fork_status
{
	PICKABLE = 1,
	NOT_PICKABLE = 0
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
	int					fork_status;
	pthread_mutex_t		fork_mtx;
}	t_fork;

typedef struct s_com
{
	pthread_mutex_t	log_mtx;
	struct timeval	start_time;
	long			time_eat;
	long			time_sleep;
	long			time_die;
	int				full_cnt;
	int				all_full;
}	t_com;

typedef struct s_info
{
	int				id;
	int				total_eat;
	long			last_eat;
	t_fork			*left;
	t_fork			*right;
}	t_info;

#endif