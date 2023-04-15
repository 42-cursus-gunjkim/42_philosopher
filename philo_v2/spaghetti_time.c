/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:40:32 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/15 20:14:38 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_check(pthread_mutex_t *mtx, void *target, long value)
{
	int ret;
	long	*tmp;

	pthread_mutex_lock(mtx);
	tmp = (long *)target;
	ret = (*tmp) - value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	safe_set(pthread_mutex_t *mtx, void *target, long value)
{
	long	*tmp;

	pthread_mutex_lock(mtx);
	tmp = (long *)target;
	(*tmp) = value;
	pthread_mutex_unlock(mtx);
}

void	monitor(t_philo *philos, t_com *common)
{
	int	i;
	int	all_done;

	while (1)
	{
		i = 0;
		all_done = 1;
		usleep(200);
		while (i < common->philo_cnt)
		{
			if ((safe_check(&philos[i].last_eat_mtx, &philos[i].last_eat, \
			 get_time(&common->start_time)) * -1) >= common->time_die)
			 {
				safe_set(&common->ttd_mtx, &common->ttd, 1);
				print_log(&philos[i], DEATH);
				return ;
			 }
			 
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(MILLI * philo->common->time_eat);
	while (safe_check(&philo->common->ttd_mtx, &philo->common->ttd, 1) != 0)
	{
		if (philo->id % 2 == 0)
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

void	spaghetti_time(t_com *common, t_philo *philos)
{
	int i;

	i = 0;
	gettimeofday(&common->start_time, NULL);
	while (i < common->philo_cnt)
	{
		philos[i].last_eat = get_time(&common->start_time);
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		i++;
	}
	monitor(philos, common);
	i = 0;
	while (i < common->philo_cnt)
		pthread_join(philos[i++].thread, NULL);
}