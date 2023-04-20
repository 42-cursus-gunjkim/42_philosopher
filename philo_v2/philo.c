/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:06:32 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 00:41:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_com *common, t_fork **forks, t_philo **philos, int i)
{
	*forks = (t_fork *)malloc(sizeof(t_fork) * common->philo_cnt);
	*philos = (t_philo *)malloc(sizeof(t_philo) * common->philo_cnt);
	if (*forks == NULL || *philos == NULL)
	{
		free(*forks);
		free(*philos);
		return (FAIL);
	}
	while (i < common->philo_cnt)
	{
		if (pthread_mutex_init(&(*forks)[i].fork_mtx, NULL) != 0 || \
		pthread_mutex_init(&(*philos)[i].last_eat_mtx, NULL) != 0 || \
		pthread_mutex_init(&(*philos)[i].full_mtx, NULL) != 0)
			return (FAIL);
		(*forks)[i].status = PICKABLE;
		(*philos)[i].id = i + 1;
		(*philos)[i].total_eat = 0;
		(*philos)[i].full = FALSE;
		(*philos)[i].left = &(*forks)[i];
		(*philos)[i].right = &(*forks)[(i + 1) % common->philo_cnt];
		(*philos)[i++].common = common;
	}
	return (SUCCESS);
}

void	philo_gc(t_fork *forks, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos[0].common->log_mtx);
	pthread_mutex_destroy(&philos[0].common->ttd_mtx);
	while (i < philos[0].common->philo_cnt)
	{
		pthread_mutex_destroy(&philos[i].full_mtx);
		pthread_mutex_destroy(&philos[i].last_eat_mtx);
		pthread_mutex_destroy(&forks[i].fork_mtx);
		i++;
	}
	free(forks);
	free(philos);
}

int	main(int argc, char *argv[])
{
	t_com	common;
	t_fork	*forks;
	t_philo	*philos;

	if ((argc != 5 && argc != 6) || !parse_arg(argc, argv, &common))
		return (0);
	if (!init(&common, &forks, &philos, 0))
	{
		philo_gc(forks, philos);
		return (0);
	}
	if (spaghetti_time(&common, philos) == FAIL)
		printf("thread create fail\n");
	philo_gc(forks, philos);
	return (0);
}
