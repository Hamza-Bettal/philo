/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:50:04 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/10 11:10:18 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	no_overflow(int sign, unsigned long long n, int count)
{
	if ((n > LLONG_MAX || count > 19) && sign == -1)
		(write(2, "Error\n", 6), exit(1));
	if ((n > LLONG_MAX || count > 19) && sign == 1)
		(write(2, "Error\n", 6), exit(1));
	return (n * sign);
}

long	ft_atoi(char *str)
{
	int		i;
	int		count;
	int		sign;
	long	n;

	i = 0;
	count = 0;
	sign = 1;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		(write(2, "Error\n", 6), exit(1));
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			(write(2, "Error\n", 6), exit(1));
		n = (n * 10) + (str[i++] - '0');
		count++;
	}
	return (no_overflow(sign, n, count));
}

int	parse(char **av, int ac)
{
	int	i;

	i = 1;
	if (ac > 4 && ac < 7)
	{
		if (ft_atoi(av[i]) <= 0)
			return (write(2, "wrong input\n", 12), 1);
		while (av[++i])
		{
			if (ft_atoi(av[i]) < 0)
				return (write(2, "wrong input\n", 12), 1);
		}
	}
	else
		return (write(2, "wrong input\n", 12), 1);
	return (0);
}