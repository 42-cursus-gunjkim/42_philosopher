/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:31:30 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/11 19:53:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_change(pthread_mutex_t *mtx, int *target, int value)
{
	pthread_mutex_lock(mtx);
	*target = value;
	pthread_mutex_unlock(mtx);
}

int	save_check(pthread_mutex_t *mtx, int *target, int value)
{
	int	ret;

	pthread_mutex_lock(mtx);
	if (*target == value)
		ret = 1;
	else
		ret = -1;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	*life_of_philo(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	if (info->id % 2 == 0)
		usleep(info->com->time_eat * MILLI);
	while (save_check(&info->ttd_lock, &info->time_to_die, 1) == -1)
	{
		philo_eat(info);
		if (info->total >= info->com->full && info->com->full != -1)
		{
			save_change(&info->info_lock, &info->done, 1);
			return (NULL);
		}
		philo_sleep_think(info);
	}
	return (NULL);
}

void	suicide_squad(t_info *infos, int philo_count, int first_suicde)
{
	long long	diff;
	int			i;

	i = 0;
	pthread_mutex_unlock(&infos[i].info_lock);
	pthread_mutex_lock(&infos[0].com->log);
	diff = diff_time(&infos[0].com->start_time, &infos[0].com->cur);
	printf("%lld %d died\n", diff, infos[first_suicde].id);
	while (i < philo_count)
		save_change(&infos[i].ttd_lock, &infos[i++].time_to_die, 1);
	pthread_mutex_unlock(&infos[0].com->log);
	return ;
}

void	monitor(t_info *infos, int philo_count)
{
	int				i;

	while (1)
	{
		i = 0;
		infos[0].com->all_full = 1;
		while (i < philo_count)
		{
			pthread_mutex_lock(&infos[i].info_lock);
			infos[0].com->all_full *= infos[i].done;
			pthread_mutex_unlock(&infos[i].info_lock);
			usleep(200);
			pthread_mutex_lock(&infos[i].info_lock);
			gettimeofday(&infos[i].com->cur, NULL);
			if (!infos[i].ing && diff_time(&infos[i].last, &infos[i].com->cur) \
			>= infos->com->time_die && infos[i].done == 0)
			if (save_check(&infos[i].info_lock, &infos[i].ing, 0) && \
			)
			{
				suicide_squad(infos, philo_count, i);
				return ;
			}
			pthread_mutex_unlock(&infos[i++].info_lock);
		}
		if (infos[0].com->all_full == 1)
			return ;
	}
}

void	spaghetti_time(pthread_t *philos, t_info *infos, int philo_count)
{
	int	i;

	i = 0;
	gettimeofday(&infos[0].com->start_time, NULL);
	while (i < philo_count)
	{
		gettimeofday(&infos[i].last, NULL);
		pthread_create(&philos[i], NULL, life_of_philo, (void *)(&infos[i]));
		pthread_detach(philos[i]);
		i++;
	}
	monitor(infos, philo_count);
}
