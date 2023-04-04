/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:43:37 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/04 21:36:48 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grap_two_fork(t_info *info)
{
	pthread_mutex_lock(&(info->left->key));
	gettimeofday(&info->cur, NULL);
	put_log_msg(FORK, info);
	pthread_mutex_lock(&(info->right->key));
	gettimeofday(&info->cur, NULL);
	put_log_msg(FORK, info);
}

void	eat_spaghetti(t_info *info)
{
	gettimeofday(&info->last_eat, NULL);
	gettimeofday(&info->cur, NULL);
	put_log_msg(EAT, info);
	info->total++;
	usleep(info->common->time_eat * MILLI);
	pthread_mutex_unlock(&(info->left->key));
	pthread_mutex_unlock(&(info->right->key));
}

void	philo_sleep_finally_think(t_info *info)
{
	gettimeofday(&info->cur, NULL);
	put_log_msg(SLEEP, info);
	usleep(info->common->time_sleep * MILLI);
	gettimeofday(&info->cur, NULL);
	put_log_msg(THINK, info);
	usleep(50);
}
