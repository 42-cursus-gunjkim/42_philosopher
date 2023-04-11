/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:43:37 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 04:52:48 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	diff_time(struct timeval *t1, struct timeval *t2)
{
	return ((t2->tv_sec - t1->tv_sec) * MILLI + \
	(t2->tv_usec / MILLI - t1->tv_usec / MILLI));
}

void	put_log_msg(int state, t_info *info)
{
	long long		diff;
	struct timeval	cur;

	pthread_mutex_lock(&info->com->log);
	pthread_mutex_lock(&info->ttd_lock);
	if (info->time_to_die == 1)
	{
		pthread_mutex_unlock(&info->ttd_lock);
		return ;
	}
	pthread_mutex_unlock(&info->ttd_lock);
	gettimeofday(&cur, NULL);
	diff = diff_time(&info->com->start_time, &cur);
	if (state == FORK)
		printf("%lld %d has taken a fork\n", diff, info->id);
	else if (state == EAT)
		printf("%lld %d is eating\n", diff, info->id);
	else if (state == SLEEP)
		printf("%lld %d is sleeping\n", diff, info->id);
	else if (state == THINK)
		printf("%lld %d is thinking\n", diff, info->id);
	else if (state == DEATH)
		printf("%lld %d died\n", diff, info->id);
	pthread_mutex_unlock(&info->com->log);
}

void	get_time(long long time)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while (diff_time(&start, &end) < time)
	{
		usleep(100);
		gettimeofday(&end, NULL);
	}
}

void	philo_eat(t_info *info)
{
	pthread_mutex_lock(&(info->left->key));
	put_log_msg(FORK, info);
	pthread_mutex_lock(&(info->right->key));
	put_log_msg(FORK, info);
	pthread_mutex_lock(&info->info_lock);
	gettimeofday(&info->last, NULL);
	info->ing = 1;
	pthread_mutex_unlock(&info->info_lock);
	put_log_msg(EAT, info);
	info->total++;
	get_time(info->com->time_eat);
	pthread_mutex_lock(&info->info_lock);
	info->ing = 0;
	pthread_mutex_unlock(&info->info_lock);
	pthread_mutex_unlock(&(info->left->key));
	pthread_mutex_unlock(&(info->right->key));
}

void	philo_sleep_think(t_info *info)
{
	put_log_msg(SLEEP, info);
	get_time(info->com->time_sleep);
	put_log_msg(THINK, info);
	usleep(100);
}
