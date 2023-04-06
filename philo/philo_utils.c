/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:43:37 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 01:10:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(long long time)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while (diff_time(&start, &end) < time)
	{
		usleep(100);
		gettimeofday(&end, NULL);
	}
}

void	grap_two_fork(t_info *info)
{
	pthread_mutex_lock(&(info->left->key));
	put_log_msg(FORK, info);
	pthread_mutex_lock(&(info->right->key));
	put_log_msg(FORK, info);
}

void	eat_spaghetti(t_info *info)
{
	pthread_mutex_lock(&info->info_lock);
	gettimeofday(&info->last_eat, NULL);
	pthread_mutex_unlock(&info->info_lock);
	put_log_msg(EAT, info);
	info->total++;
	get_time(info->common->time_eat);
	pthread_mutex_unlock(&(info->left->key));
	pthread_mutex_unlock(&(info->right->key));
}

void	philo_sleep_finally_think(t_info *info)
{
	put_log_msg(SLEEP, info);
	get_time(info->common->time_sleep);
	put_log_msg(THINK, info);
	usleep(100);
}
