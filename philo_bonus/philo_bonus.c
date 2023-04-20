/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:43 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 02:10:16 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_com	common;
	sem_t	*forks;

	if ((argc != 5 && argc != 6) || !parse_arg(argc, argv, &common))
		return (0);
	forks = sem_open("forks", O_CREAT, S_IXUSR, common.philo_cnt);
	if (forks == -1)
		return (0);
	spaghetti_time(forks, &common);
	sem_close(forks);
	sem_unlink(forks);
	return (0);
}
