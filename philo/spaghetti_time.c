/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:40:32 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/28 11:23:25 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_philo *philos, t_com *common)
{
	int	i;

	while (1)
	{
		i = 0;
		common->all_done = TRUE;
		usleep(100);
		while (i < common->philo_cnt)
		{
			if (common->full_cnt != NO_FULL_CNT)
				s_mul(&philos[i].full_mtx, &philos[i].full, &common->all_done);
			pthread_mutex_lock(&philos[i].last_eat_mtx);
			if (get_time(&common->start_time) - philos[i].last_eat \
			>= common->time_die)
			{
				s_set_int(&common->ttd_mtx, &(common->ttd), 1);
				print_log(&philos[i], DEATH);
				pthread_mutex_unlock(&philos[i].last_eat_mtx);
				return ;
			}
			pthread_mutex_unlock(&philos[i].last_eat_mtx);
			i++;
		}
		if (common->full_cnt != NO_FULL_CNT && common->all_done == TRUE)
		{
			s_set_int(&common->ttd_mtx, &(common->ttd), 1);
			return ;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500 * philo->common->time_eat);
	while ( s_check_int(&philo->common->ttd_mtx, &philo->common->ttd, 1) != 0)
	{
		if (philo->id % 2 == 1 || philo->common->philo_cnt % 2 == 1)
		{
			take_forks(philo, LEFT);
			take_forks(philo, RIGHT);
		}
		else
		{
			take_forks(philo, RIGHT);
			take_forks(philo, LEFT);
		}
		philo_eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		print_log(philo, THINK);
		usleep(100);
	}
	return (NULL);
}

int	spaghetti_time(t_com *common, t_philo *philos)
{
	int	i;

	i = 0;
	gettimeofday(&common->start_time, NULL);
	while (i < common->philo_cnt)
	{
		philos[i].last_eat = get_time(&common->start_time);
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (FAIL);
		i++;
	}
	monitor(philos, common);
	i = 0;
	while (i < common->philo_cnt)
		pthread_join(philos[i++].thread, NULL);
	return (SUCCESS);
}
