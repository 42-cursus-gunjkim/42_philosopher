/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:13:48 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 05:41:03 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	spend_time(long time, t_philo *philo)
{
	long	start_time;

	start_time = get_time(&philo->common->start_time);
	while (get_time(&philo->common->start_time) - start_time < time)
		usleep(200);
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

	sem_wait(philo->common->log_sem);
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
	{
		printf("%ld %d died\n", log_time, philo->id);
		return ;
	}
	sem_post(philo->common->log_sem);
}
