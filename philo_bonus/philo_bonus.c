/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:45:43 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 05:43:52 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_com	common;

	if ((argc != 5 && argc != 6) || !parse_arg(argc, argv, &common))
		return (0);
	spaghetti_time(&common);
	sem_close(common.forks);
	sem_unlink("forks");
	sem_close(common.log_sem);
	sem_unlink("log");
	sem_close(common.simul);
	sem_unlink("simul");
	return (0);
}
