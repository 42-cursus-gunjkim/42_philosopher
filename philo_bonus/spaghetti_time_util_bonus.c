/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_time_util_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:58 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 05:59:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	sem_wait(philo->common->forks);
	print_log(philo, PICK);
	sem_wait(philo->common->forks);
	print_log(philo, PICK);
	philo->last_eat = get_time(&philo->common->start_time);
	print_log(philo, EAT);
	spend_time(philo->common->time_eat, philo);
	sem_post(philo->common->forks);
	sem_post(philo->common->forks);
	print_log(philo, SLEEP);
	spend_time(philo->common->time_sleep, philo);
	print_log(philo, THINK);
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(300);
		if (get_time(&philo->common->start_time) - philo->last_eat \
		>= philo->common->time_die)
		{
			print_log(philo, DEATH);
			sem_post(philo->common->simul);
			break ;
		}
	}
	return (NULL);
}
