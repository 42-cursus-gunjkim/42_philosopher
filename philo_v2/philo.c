/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:06:32 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/20 18:28:15 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_com *common, t_fork **forks, t_philo **philos)
{
	int	i;

	i = 0;
	*forks = (t_fork *)malloc(sizeof(t_fork) * common->philo_cnt);
	if (*forks == NULL)
		return (FALSE);
	*philos = (t_philo *)malloc(sizeof(t_philo) * common->philo_cnt);
	if (*philos == NULL)
	{
		free(*forks);
		return (FALSE);
	}
	common->ttd = FALSE;
	pthread_mutex_init(&common->ttd_mtx, NULL);
	while (i < common->philo_cnt)
	{
		(*forks)[i].status = PICKABLE;
		pthread_mutex_init(&(*forks)[i].fork_mtx, NULL);
		pthread_mutex_init(&(*philos)[i].last_eat_mtx, NULL);
		(*philos)[i].id = i + 1;
		(*philos)[i].total_eat = 0;
		(*philos)[i].left = &(*forks)[i];
		(*philos)[i].right = &(*forks)[(i + 1) % common->philo_cnt];
		(*philos)[i++].common = common;
	}
	return (TRUE);
}

void	philo_gc(t_fork *forks, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos[0].common->log_mtx);
	pthread_mutex_destroy(&philos[0].common->ttd_mtx);
	while (i < philos[0].common->philo_cnt)
	{
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
	if (!init(&common, &forks, &philos))
		return (0);
	spaghetti_time(&common, philos);
	philo_gc(forks, philos);
}
