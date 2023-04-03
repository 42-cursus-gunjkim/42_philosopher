/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:12:23 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/31 20:16:43 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	print_state(int state)
{
	if (state == FORK)
		put_str(" has taken a fork\n");
	else if (state == EAT)
		put_str(" is eating\n");
	else if (state == SLEEP)
		put_str(" is sleeping\n");
	else if (state == THINK)
		put_str(" is thinking\n");
	else if (state == DEATH)
		put_str(" died\n");
}

int	diff_time(struct timeval *t1, struct timeval *t2)
{
	return ((t2->tv_sec - t1->tv_sec) * 1000 + \
	(t2->tv_usec - t1->tv_usec) / 1000);
}

void	put_log_msg(int	state, int	id, t_common *common)
{
	struct timeval	cur_time;
	char			*diff;
	char			*id_str;

	pthread_mutex_lock(common->log);
	gettimeofday(&cur_time, NULL);
	diff = ft_itoa(diff_time(&common->start_time ,&cur_time));
	put_str(diff);
	free(diff);
	diff = NULL;
	id_str = ft_itoa(id);
	put_str(" ");
	put_str(id_str);
	free(id_str);
	id_str = NULL;
	print_state(state);
	pthread_mutex_unlock(common->log);
}
