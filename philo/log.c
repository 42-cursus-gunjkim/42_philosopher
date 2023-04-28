/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:42:45 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/28 11:13:03 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spend_time(long time, t_philo *philo)
{
	long	start_time;

	start_time = get_time(&philo->common->start_time);
	while (get_time(&philo->common->start_time) - start_time < time)
		usleep(100);
}

long	get_time(struct timeval *start_time)
{
	struct timeval	cur_time;
	long			result;

	gettimeofday(&cur_time, NULL);
	result = (cur_time.tv_sec - start_time->tv_sec) * 1000;
	result += (cur_time.tv_usec / 1000 - start_time->tv_usec / 1000);
	return (result);
}

void	print_log(t_philo *philo, int status)
{
	long	log_time;

	pthread_mutex_lock(&philo->common->log_mtx);
	if (s_check_int(&philo->common->ttd_mtx, &philo->common->ttd, 1) == 0 \
	&& status != DEATH)
	{
		pthread_mutex_unlock(&philo->common->log_mtx);
		return ;
	}
	log_time = get_time(&philo->common->start_time);
	if (status == PICK)
		printf("%ld %d has taken a fork\n", log_time, philo->id);
	else if (status == EAT)
		printf("%ld %d is eating\n", log_time, philo->id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", log_time, philo->id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", log_time, philo->id);
	else if (status == DEATH)
		printf("%ld %d died\n", log_time, philo->id);
	pthread_mutex_unlock(&philo->common->log_mtx);
}
