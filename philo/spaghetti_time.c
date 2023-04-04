/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:31:30 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/04 21:36:07 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	if (info->id % 2 == 0)
		usleep(info->common->time_eat * MILLI);
	while (info->time_to_die != 1)
	{
		if (info->total >= info->common->full && info->common->full != -1)
		{
			info->done = 1;
			return (NULL);
		}
		grap_two_fork(info);
		eat_spaghetti(info);
		philo_sleep_finally_think(info);
	}
	return (NULL);
}

void	monitor(t_info *infos, int philo_count)
{
	int				i;
	int				all_full;
	long long		diff;

	while (1)
	{
		i = 0;
		all_full = 1;
		while (i < philo_count)
		{
			all_full *= infos[i].done;
			gettimeofday(&infos[i].cur, NULL);
			if (diff_time(&infos[i].last_eat, &infos[i].cur) \
			>= infos->common->time_die && infos[i].done == 0)
			{
				pthread_mutex_lock(&infos[i].common->log);
				diff = diff_time(&infos[i].common->start_time, &infos[i].cur);
				printf("%lld %d died\n", diff, infos[i].id);
				i = 0;
				while (i < philo_count)
					infos[i++].time_to_die = 1;
				return ;
			}
			i++;
		}
		if (all_full == 1)
		{
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
	return (1);
}
