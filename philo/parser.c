/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/04 19:28:16 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atol(const char *str)
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

int	parse_argv(int argc, char *argv[], t_common *common, int *philo_count)
{
	*philo_count = ft_atol(argv[1]);
	common->time_die = ft_atol(argv[2]);
	common->time_eat = ft_atol(argv[3]);
	common->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		common->full = ft_atol(argv[5]);
	else
		common->full = NO_TIME_FULL;
	if (*philo_count <= 0 || common->time_die < 0 || common->time_eat < 0 || \
	common->time_sleep < 0 || (common->full < 0 && argc == 6))
		return (-1);
	return (1);
}
