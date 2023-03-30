/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:14:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/03/30 21:19:57 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_time
{
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_full;
}	t_time;

typedef struct s_philo
{
	t_time			*time;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

#endif
