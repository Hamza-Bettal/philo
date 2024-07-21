/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:50:04 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/21 17:37:44 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleaner(t_philo *philo)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("dead_sem");
	sem_unlink("done_sem");
	if (sem_close(philo->data->dead_sem) == -1)
		printf("error");
	if (sem_close(philo->data->forks_sem) == -1)
		printf("error");
	if (sem_close(philo->data->done_sem) == -1)
		printf("error");
	if (sem_close(philo->data->print_sem) == -1)
		printf("error");
	free(philo);
}

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

int	parsing(int ac, char **av)
{
	if (ac > 4 && ac < 7)
	{
		if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) >= 200)
			return (write(2, "wrong input\n", 12), 1);
			if (ft_atoi(av[2]) < 61 || ft_atoi(av[3]) < 61 || ft_atoi(av[4]) < 61)
				return (write(2, "wrong input\n", 12), 1);
		if (av[5] && ft_atoi(av[5]) < 0)
			return (write(2, "wrong input\n", 12), 1);
	}
	else
		return (write(2, "wrong input\n", 12), 1);
	return (0);
}
