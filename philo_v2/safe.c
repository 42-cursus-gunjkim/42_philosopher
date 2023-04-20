/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:38:27 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/20 17:49:34 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	safe_check_long(pthread_mutex_t *mtx, long *target, long value)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = (*target) - value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	safe_set_long(pthread_mutex_t *mtx, long *target, long value)
{
	pthread_mutex_lock(mtx);
	(*target) = value;
	pthread_mutex_unlock(mtx);
}

int	safe_check_int(pthread_mutex_t *mtx, int *target, int value)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = (*target) - value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	safe_set_int(pthread_mutex_t *mtx, int *target, int value)
{
	pthread_mutex_lock(mtx);
	(*target) = value;
	pthread_mutex_unlock(mtx);
}
