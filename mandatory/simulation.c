/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:55:14 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/09 20:23:09 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(int time)
{
	size_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}

void ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d %s\n", get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(&philo->table->print);
}
void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while(1)
	{
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
	}
} 

void	start_simulation(t_philo *philo, t_table *table)
{

	int i;

	i = 0;
	while (i < philo->table->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_life, &philo[i]);
		pthread_detach(philo[i].thread);
		i++;
	}
	while (1)
		;
}
