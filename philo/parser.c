/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/07 04:53:07 by gunjkim          ###   ########.fr       */
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

int	parse_argv(int argc, char *argv[], t_com *com, int *philo_count)
{
	*philo_count = ft_atol(argv[1]);
	com->time_die = ft_atol(argv[2]);
	com->time_eat = ft_atol(argv[3]);
	com->time_sleep = ft_atol(argv[4]);
	com->all_full = 0;
	if (argc == 6)
		com->full = ft_atol(argv[5]);
	else
		com->full = NO_TIME_FULL;
	if (*philo_count <= 0 || com->time_die < 0 || com->time_eat < 0 || \
	com->time_sleep < 0 || (com->full < 0 && argc == 6))
		return (-1);
	return (1);
}
