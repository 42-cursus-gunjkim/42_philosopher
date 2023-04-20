/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:10:41 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 02:26:56 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if (philo->last_eat >= philo->common->time_eat)
		{

		}
	}
}

void	philo_do(t_philo *philo, sem_t *forks)
{
	pthread_t	monitor;

	pthread_create(*monitor, NULL, routine, philo);
}

void	init_philo(t_philo *philo, int id, t_com *common)
{
	philo->id = id;
	philo->common = common;
	philo->total_eat = 0;
	philo->last_eat = get_time(&common->start_time);
}

int	spaghetti_time(sem_t *forks, t_com *common)
{
	int		i;
	int		p_cnt;
	int		status;
	t_philo	philo;

	i = 0;
	p_cnt = 0;
	gettimeofday(&common->start_time, NULL);
	while (i < common->philo_cnt)
	{
		init_philo(&philo, i + 1, common);
		philo.pid = fork();
		if (philo.pid == 0)
			philo_do(&philo, forks);
		else if (philo.pid < 0)
			return (FAIL);
	}
	while (p_cnt < common->philo_cnt)
	{
		wait(&status);
		p_cnt++;
	}
	return (SUCCESS);
}
