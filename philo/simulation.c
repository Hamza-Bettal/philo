/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:55:14 by hbettal           #+#    #+#             */
/*   Updated: 2024/08/02 12:47:08 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d %s\n", get_time() - philo->start, philo->id, str);
	if (ft_strncmp(str, "died", 4))
		pthread_mutex_unlock(&philo->table->print);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(50);
}

void	check_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (philo->table->num_of_philo == 1)
	{
		ft_usleep(philo->table->time_to_die);
		philo->table->dead = 1;
		pthread_mutex_unlock(&philo->table->meal_mutex);
		ft_printf(philo, "died");
		return ;
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_lock(philo->l_fork);
	ft_printf(philo, "has taken a fork");
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (philo->table->num_of_meals != -1)
		philo->table[philo->id - 1].num_of_meals--;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_lock(&philo->table->dead_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->dead_mutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		check_forks(philo);
		pthread_mutex_lock(&philo->table->meal_mutex);
		if (philo->table[philo->id - 1].num_of_meals == 0)
		{
			philo->table->k++;
			pthread_mutex_unlock(&philo->table->meal_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->meal_mutex);
		ft_printf(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		ft_printf(philo, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_philo *philo, t_table *table)
{
	int			i;
	int			j;
	pthread_t	thread;

	1 && (i = -1, j = philo->table->num_of_meals);
	while (++i < philo->table->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		pthread_detach(philo[i].thread);
	}
	pthread_create(&thread, NULL, monitoring, table);
	pthread_join(thread, NULL);
	i = -1;
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	(free(table->forks), free(table), free(philo));
}
