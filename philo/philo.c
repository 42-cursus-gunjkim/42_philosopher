/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:14:12 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/31 20:13:38 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_fork(int philo_count)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * philo_count);
	if (forks == NULL)
		return (NULL);
	while (i < philo_count)
	{
		forks[i].status = 0;
		if (pthread_mutex_init(&forks[i].key, NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_info	*init_infos(t_fork *fork, t_com *com, int philo_count)
{
	int		i;
	t_info	*infos;

	i = 0;
	infos = (t_info *)malloc(sizeof(t_info) * philo_count);
	if (infos == NULL)
	{
		free(fork);
		return (NULL);
	}
	while (i < philo_count)
	{
		infos[i].id = i + 1;
		infos[i].total = 0;
		infos[i].left = &fork[i];
		infos[i].right = &fork[(i + 1) % philo_count];
		infos[i].com = com;
		infos[i].time_to_die = 0;
		infos[i].ing = 0;
		pthread_mutex_init(&infos[i].ttd_lock, NULL);
		pthread_mutex_init(&infos[i].info_lock, NULL);
		i++;
	}
	return (infos);
}

void	clear_exit(pthread_t *philos, t_fork *forks, t_info *infos)
{
	free(philos);
	free(infos);
	free(forks);
}

int	argv_check(int argc, char **argv, t_com *com, int *philo_count)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (parse_argv(argc, argv, com, philo_count) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t		*philos;
	t_com			com;
	t_fork			*forks;
	t_info			*infos;
	int				philo_count;

	if (argv_check(argc, argv, &com, &philo_count) == -1)
		return (0);
	pthread_mutex_init(&com.log, NULL);
	forks = init_fork(philo_count);
	if (forks == NULL)
		return (0);
	infos = init_infos(forks, &com, philo_count);
	if (infos == NULL)
		return (0);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (philos == NULL)
	{
		free(infos);
		free(forks);
		return (0);
	}
	spaghetti_time(philos, infos, philo_count);
	clear_exit(philos, forks, infos);
	return (0);
}
