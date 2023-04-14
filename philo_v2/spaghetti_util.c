/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:13:48 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/14 21:50:24 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	print_log(philo, EAT);
	philo->last_eat = get_time(&philo->common->start_time);
	spend_time(philo->common->time_eat, philo);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, SLEEP);
	spend_time(philo->common->time_sleep, philo);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->fork_mtx);
	philo->left->status = PICKABLE;
	pthread_mutex_unlock(&philo->left->fork_mtx);
	pthread_mutex_lock(&philo->right->fork_mtx);
	philo->right->status = PICKABLE;
	pthread_mutex_unlock(&philo->right->fork_mtx);
}

void	take_forks(t_philo *philo, int hand)
{
	t_fork	*fork;

	if (hand == LEFT)
		fork = philo->left;
	else
		fork = philo->right;
	while (1)
	{
		if (fork->status == PICKABLE)
		{
			pthread_mutex_lock(&fork->fork_mtx);
			if (fork->status == PICKABLE)
			{
				fork->status = PICKED;
				pthread_mutex_unlock(&fork->fork_mtx);
				break ;
			}
			pthread_mutex_unlock(&fork->fork_mtx);
		}
		usleep(100);
	}
	print_log(philo, PICK);
}