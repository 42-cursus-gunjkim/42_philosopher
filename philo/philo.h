/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:14:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/02 19:45:06 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_H
# define philo_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define NO_TIME_FULL -1
# define FORK 0
# define EAT 1
# define THINK 2
# define SLEEP 3
# define DEATH 4

typedef struct s_common
{
	pthread_mutex_t	*log;
	struct timeval	start_time;
	int				time_die;
	int				time_eat;
	int				time_think;
	int				time_sleep;
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
	int				time_to_die;
	t_common		*common;
	struct timeval	last_eat;
	t_fork			*left;
	t_fork			*right;
}	t_info;

char	*ft_itoa(int n);
int		parse_argv(int argc, char *argv[], t_common *common, int *philo_count);
int		spaghetti_time(t_info *infos, int philo_count);
void	put_log_msg(int	state, int	id, t_common *common);
int		diff_time(struct timeval *t1, struct timeval *t2);

#endif
