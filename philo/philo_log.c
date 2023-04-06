/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:12:23 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/31 20:16:43 by gunjkim          ###   ########.fr       */
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

	pthread_mutex_lock(&info->common->log);
	pthread_mutex_lock(&info->ttd_lock);
	if (info->time_to_die == 1)
	{
		pthread_mutex_unlock(&info->ttd_lock);
		return ;
	}
	pthread_mutex_unlock(&info->ttd_lock);
	gettimeofday(&cur, NULL);
	diff = diff_time(&info->common->start_time, &cur);
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
	pthread_mutex_unlock(&info->common->log);
}
