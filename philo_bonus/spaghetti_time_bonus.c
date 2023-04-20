/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:10:41 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 06:00:10 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_do(t_philo *philo)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, philo_monitor, philo);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		usleep(philo->common->time_eat * 1000);
	while (1)
	{
		philo_routine(philo);
		usleep(100);
	}
}

void	init_philo(t_philo *philo, int id, t_com *common)
{
	philo->id = id;
	philo->common = common;
	philo->total_eat = 0;
	philo->last_eat = get_time(&common->start_time);
}

void	kill_all_process(pid_t *pid_arr, int philo_cnt)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo_cnt)
		kill(pid_arr[i++], SIGINT);
	i = 0;
	while (i < philo_cnt)
		waitpid(pid_arr[i++], &status, 0);
}

int	spaghetti_time(t_com *common)
{
	int		i;
	int		p_cnt;
	pid_t	*pid_arr;
	t_philo	philo;

	i = 0;
	p_cnt = 0;
	pid_arr = (pid_t *)malloc(sizeof(pid_t) * common->philo_cnt);
	gettimeofday(&common->start_time, NULL);
	sem_wait(common->simul);
	while (i < common->philo_cnt)
	{
		init_philo(&philo, i + 1, common);
		pid_arr[i] = fork();
		if (pid_arr[i] == 0)
			philo_do(&philo);
		else if (pid_arr[i] < 0)
			return (FAIL);
		i++;
	}
	sem_wait(common->simul);
	kill_all_process(pid_arr, common->philo_cnt);
	free(pid_arr);
	return (SUCCESS);
}
