/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/04/02 21:55:04 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	d_count(int n)
{
	size_t	dc;

	dc = 0;
	if (n <= 0)
		dc++;
	while (n != 0)
	{
		dc++;
		n = n / 10;
	}
	return (dc);
}

char	*ft_itoa(int n)
{
	size_t		dc;
	char		*result;
	long long	n_tmp;	

	dc = d_count(n);
	n_tmp = (long long)n;
	if (n_tmp < 0)
		n_tmp = n_tmp * -1;
	result = malloc(sizeof(char) * (dc + 1));
	if (result == NULL)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	result[dc--] = '\0';
	while (n_tmp > 9)
	{
		result[dc--] = n_tmp % 10 + '0';
		n_tmp = n_tmp / 10;
	}
	result[dc] = n_tmp + '0';
	return (result);
}

static int	ft_atoi(const char *str)
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
	*philo_count = ft_atoi(argv[1]);
	common->time_die = ft_atoi(argv[2]);
	common->time_eat = ft_atoi(argv[3]);
	common->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		common->full = ft_atoi(argv[5]);
	else
		common->full = NO_TIME_FULL;
	if (*philo_count <= 0 || common->time_die < 0 || common->time_eat < 0 || \
	common->time_sleep < 0 || (common->full < 0 && argc == 6))
		return (-1);
	return (1);
}
