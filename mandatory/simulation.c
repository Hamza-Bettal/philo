/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:55:14 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/10 11:53:17 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(size_t time)
{
	size_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d %s\n", get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int 	i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (++i == philo->table->num_of_meals)
			return (philo->table->dead = 1, NULL);
		ft_printf(philo, "is thinking");
		pthread_mutex_lock(philo->r_fork);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		ft_printf(philo, "has taken a fork");
		ft_printf(philo, "is eating");
		philo->last_meal = get_time();
		ft_usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		ft_printf(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		if (get_time() - philo->last_meal >= philo->table->time_to_die)
		{
			ft_printf(philo, "died");
			philo->table->dead = 1;
			return (NULL);
		}
	}
} 

void	start_simulation(t_philo *philo, t_table *table)
{

	int i;

	i = -1;
	(void)table;
	while (++i < philo->table->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		pthread_detach(philo[i].thread);
	}
	while (!table->dead)
		;
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	free(table->forks);
	free(table);
	free(philo);
}
