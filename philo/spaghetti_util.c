/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:13:48 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/28 11:18:21 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	s_set_long(&philo->last_eat_mtx, &philo->last_eat, \
	get_time(&philo->common->start_time));
	print_log(philo, EAT);
	spend_time(philo->common->time_eat, philo);
	philo->total_eat++;
	if (philo->common->full_cnt != NO_FULL_CNT \
	& philo->total_eat == philo->common->full_cnt)
		s_set_int(&philo->full_mtx, &philo->full, TRUE);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, SLEEP);
	spend_time(philo->common->time_sleep, philo);
}

void	put_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->id % 2 == 1 || philo->common->philo_cnt % 2 == 1)
	{
		first = philo->right;
		second = philo->left;
	}
	else
	{
		first = philo->left;
		second = philo->right;
	}
	s_set_int(&first->fork_mtx, &first->status, PICKABLE);
	s_set_int(&second->fork_mtx, &second->status, PICKABLE);
}

void	take_forks(t_philo *philo, int hand)
{
	t_fork	*fork;
	int		priority;

	priority = 200;
	if (hand == LEFT)
		fork = philo->left;
	else
		fork = philo->right;
	while (s_check_int(&philo->common->ttd_mtx, &philo->common->ttd, 1) != 0)
	{
		pthread_mutex_lock(&fork->fork_mtx);
		if (fork->status == PICKABLE)
		{
			fork->status = PICKED;
			pthread_mutex_unlock(&fork->fork_mtx);
			print_log(philo, PICK);
			break ;
		}
		pthread_mutex_unlock(&fork->fork_mtx);
		usleep(priority);
		if (priority > 50)
			priority -= 1;
	}
}
