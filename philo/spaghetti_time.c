/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:31:30 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/04 17:25:06 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (info->time_to_die == 1)
			return (NULL);
		pthread_mutex_lock(&(info->left->key));
		put_log_msg(FORK, info->id, info->common);
		pthread_mutex_lock(&(info->right->key));
		put_log_msg(FORK, info->id, info->common);
		put_log_msg(EAT, info->id, info->common);
		gettimeofday(&info->last_eat, NULL);
		usleep(info->common->time_eat);
		pthread_mutex_unlock(&(info->left->key));
		pthread_mutex_unlock(&(info->right->key));
		put_log_msg(SLEEP, info->id, info->common);
		usleep(info->common->time_sleep);
		put_log_msg(THINK, info->id, info->common);
		usleep(info->common->time_think);
	}
	return (NULL);
}

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

int	spaghetti_time(pthread_t *philos, t_info *infos, int philo_count)
{
	int	i;

	i = 0;
	gettimeofday(&infos[0].common->start_time, NULL);
	while (i < philo_count)
	{
		printf("%d\n", i);
		gettimeofday(&infos[i].last_eat, NULL);
		pthread_create(&philos[i], NULL, life_of_philo, (void *)(&infos[i]));
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_detach(philos[i]);
		i++;
	}
	monitor(infos, philo_count);
	return (1);
}
