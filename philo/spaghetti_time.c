/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:31:30 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/02 22:02:19 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//the functhion that thread run
void	*life_of_philo(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (info->time_to_die == 1)
			return (NULL);
		pthread_mutex_lock(&info->left->key);
		put_log_msg(FORK, info->id, info->common);
		pthread_mutex_lock(&info->right->key);
		put_log_msg(FORK, info->id, info->common);
		put_log_msg(EAT, info->id, info->common);
		gettimeofday(&info->last_eat, NULL);
		usleep(info->common->time_eat);
		pthread_mutex_unlock(&info->left->key);
		pthread_mutex_unlock(&info->right->key);
		put_log_msg(SLEEP, info->id, info->common);
		usleep(info->common->time_sleep);
		put_log_msg(THINK, info->id, info->common);
		usleep(info->common->time_think);
	}
	return (NULL);
}

//the functhin that monitor the every info->last_eat is bigger than common->time_die
//if it is bigger, set info->time_to_die is 1
void	monitor(t_info *infos, int philo_count)
{
	int				i;
	struct timeval	cur_time;

	while (1)
	{
		i = 0;
		while (i < philo_count)
		{
			gettimeofday(&cur_time, NULL);
			if (diff_time(&infos[i].last_eat, &cur_time) \
			>= infos->common->time_die)
			{
				put_log_msg(DEATH, infos[i].id, infos->common);
				i = 0;
				while (i < philo_count)
				{
					infos[i].time_to_die = 1;
					i++;
				}
				return ;
			}
			i++;
		}
	}
}

//the function that each thread create and runs and monitor the statue of the philosopher
int	spaghetti_time(t_info *infos, int philo_count)
{
	pthread_t	*philos;
	int			i;

	i = 0;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (philos == NULL)
		return (-1);
	gettimeofday(&infos[0].common->start_time, NULL);
	while (i < philo_count)
	{
		gettimeofday(&infos[i].last_eat, NULL);
		pthread_create(&philos[i], NULL, life_of_philo, (void *)(&infos[i]));
		pthread_detach(philos[i]);
		i++;
	}
	monitor(infos, philo_count);
	return (1);
}
