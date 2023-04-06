/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:31:30 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 02:29:13 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	if (info->id % 2 == 0)
		usleep(info->common->time_eat * MILLI);
	pthread_mutex_lock(&info->ttd_lock);
	while (info->time_to_die != 1)
	{
		pthread_mutex_unlock(&info->ttd_lock);
		if (info->total >= info->common->full && info->common->full != -1)
		{
			pthread_mutex_lock(&info->info_lock);
			info->done = 1;
			pthread_mutex_unlock(&info->info_lock);
			return (NULL);
		}
		grap_two_fork(info);
		eat_spaghetti(info);
		philo_sleep_finally_think(info);
		pthread_mutex_lock(&info->ttd_lock);
	}
	pthread_mutex_unlock(&info->ttd_lock);
	return (NULL);
}

void	suicide_squad(t_info *infos, int philo_count, int first_suicde)
{
	long long	diff;
	int			i;

	i = 0;
	pthread_mutex_lock(&infos[0].common->log);
	diff = diff_time(&infos[0].common->start_time, &infos[0].common->cur);
	printf("%lld %d died\n", diff, infos[first_suicde].id);
	while (i < philo_count)
	{
		pthread_mutex_lock(&infos[i].ttd_lock);
		infos[i++].time_to_die = 1;
		pthread_mutex_unlock(&infos[i].ttd_lock);
	}
	return ;
}

void	monitor(t_info *infos, int philo_count)
{
	int				i;
	int				all_full;

	while (1)
	{
		usleep(100);
		i = 0;
		all_full = 1;
		while (i < philo_count)
		{
			pthread_mutex_lock(&infos[i].info_lock);
			all_full *= infos[i].done;
			pthread_mutex_unlock(&infos[i].info_lock);
			usleep(100);
			pthread_mutex_lock(&infos[i].info_lock);
			gettimeofday(&infos[i].common->cur, NULL);
			if (diff_time(&infos[i].last_eat, &infos[i].common->cur) \
			>= infos->common->time_die && infos[i].done == 0)
			{
				pthread_mutex_unlock(&infos[i].info_lock);
				suicide_squad(infos, philo_count, i);
				return ;
			}
			pthread_mutex_unlock(&infos[i++].info_lock);
		}
		if (all_full == 1)
		{
			pthread_mutex_lock(&infos[0].common->log);
			printf("Dining is over!\n");
			return ;
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
		gettimeofday(&infos[i].last_eat, NULL);
		pthread_create(&philos[i], NULL, life_of_philo, (void *)(&infos[i]));
		pthread_detach(philos[i]);
		i++;
	}
	monitor(infos, philo_count);
	pthread_mutex_unlock(&infos->common->log);
	i = 0;
	// while (i < philo_count)
	// 	pthread_join(philos[i++], NULL);
	return (1);
}
