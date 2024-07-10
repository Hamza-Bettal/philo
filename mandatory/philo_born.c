/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_born.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:38:21 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/10 12:49:18 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int		fill_table(t_table *table, char **av, int ac)
{
	(void)ac;
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (pthread_mutex_init(&table->print, NULL) 
	|| pthread_mutex_init(&table->dead_mutex, NULL) 
	|| pthread_mutex_init(&table->meal_mutex, NULL))
		return (write(2, "Error\n", 6), 1);
	table->start = get_time();
	table->dead = 0;
	return (0);
}

int	philo_birth(char **av, int ac)
{
	t_philo	*philo;
	t_table	*table;
	int		i;
	
	i = -1;
	table = malloc(sizeof(t_table) * ft_atoi(av[1]));
	if (fill_table(table, av, ac))
		return (1);
	philo = malloc(sizeof(t_philo) * table->num_of_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!philo || !table->forks)
		(write(2, "Error\n", 6));
	philo->table = table;
	while (++i < philo->table->num_of_philo)
	{
		if (ac == 6)
			philo->table[i].num_of_meals = ft_atoi(av[5]);
		else
			philo->table[i].num_of_meals = -1;
		1 && (philo[i].id = i + 1, philo[i].start = table->start);
		1 && (philo[i].last_meal = philo[i].start, philo[i].table = table);
		philo[i].r_fork = &table->forks[i];
		philo[i].l_fork = &table->forks[(i + 1) % table->num_of_philo];
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (write(2, "Error\n", 6), 1);
	}
	start_simulation(philo, table);
	return (0);
}
