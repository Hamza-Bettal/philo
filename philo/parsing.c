/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:50:04 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/28 11:40:50 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	if (ac > 4 && ac < 7)
	{
		if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
			return (write(2, "wrong input\n", 12), 1);
		if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
			return (write(2, "wrong input\n", 12), 1);
		if (ac == 6 && ft_atoi(av[5]) < 0)
			return (write(2, "wrong input\n", 12), 1);
		if (ac == 6 && ft_atoi(av[5]) == 0)
			return (1);
	}
	else
		return (write(2, "wrong input\n", 12), 1);
	return (0);
}
