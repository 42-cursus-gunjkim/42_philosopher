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
	return ((t2->tv_sec - t1->tv_sec) * 1000 + \
	(t2->tv_usec - t1->tv_usec) / 1000);
}

void	put_log_msg(int state, t_info *info)
{
	long long		diff;

	pthread_mutex_lock(&info->common->log);
	diff = diff_time(&info->common->start_time, &info->cur);
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
