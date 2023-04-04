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

void	put_log_msg(int state, int id, t_common *common)
{
	struct timeval	cur_time;
	long long		diff;

	pthread_mutex_lock(&common->log);
	gettimeofday(&cur_time, NULL);
	diff = diff_time(&common->start_time, &cur_time);
	if (state == FORK)
		printf("%lld %d has taken a fork\n", diff, id);
	else if (state == EAT)
		printf("%lld %d is eating\n", diff, id);
	else if (state == SLEEP)
		printf("%lld %d is sleeping\n", diff, id);
	else if (state == THINK)
		printf("%lld %d is thinking\n", diff, id);
	else if (state == DEATH)
		printf("%lld %d died\n", diff, id);
	pthread_mutex_unlock(&common->log);
}
