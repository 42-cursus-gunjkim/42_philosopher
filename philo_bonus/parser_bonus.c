/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:58:06 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/21 10:38:03 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atol(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	parse_arg(int argc, char *argv[], t_com *common)
{
	common->philo_cnt = ft_atol(argv[1]);
	common->time_die = ft_atol(argv[2]);
	common->time_eat = ft_atol(argv[3]);
	common->time_sleep = ft_atol(argv[4]);
	sem_unlink("log");
	sem_unlink("forks");
	sem_unlink("simul");
	common->log_sem = sem_open("log", O_CREAT, 0600, 1);
	common->forks = sem_open("forks", O_CREAT, 0600, common->philo_cnt);
	common->simul = sem_open("simul", O_CREAT, 0600, 1);
	if (argc == 6)
		common->full_cnt = ft_atol(argv[5]);
	else
		common->full_cnt = NO_FULL_CNT;
	if (common->philo_cnt < 1 || common->time_die < 0
		|| common->time_eat < 0 || common->time_sleep < 0
		|| (common->full_cnt < 0 && argc == 6))
		return (FALSE);
	return (TRUE);
}
