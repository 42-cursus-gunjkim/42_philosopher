/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:13:48 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 02:14:02 by gunjkim          ###   ########.fr       */
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