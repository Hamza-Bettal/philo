/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:42:32 by hbettal           #+#    #+#             */
/*   Updated: 2024/08/02 12:49:56 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_done(t_table *table, int dead)
{
	pthread_mutex_lock(&table->meal_mutex);
	pthread_mutex_lock(&table->dead_mutex);
	if (dead || table->dead || table->num_of_philo == table->k)
	{
		pthread_mutex_unlock(&table->dead_mutex);
		pthread_mutex_unlock(&table->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->dead_mutex);
	pthread_mutex_unlock(&table->meal_mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal >= philo->table->time_to_die \
			&& philo->table->dead == 0)
	{
		ft_printf(philo, "died");
		philo->table->dead = 1;
		return (1);
	}
	return (0);
}

void	*monitoring(void *p)
{
	t_table	*table;
	int		i;
	int		dead;

	table = (t_table *)p;
	dead = 0;
	while (1)
	{
		if (is_done(table, dead))
			break ;
		i = -1;
		while (++i < table->num_of_philo)
		{
			pthread_mutex_lock(&table->dead_mutex);
			dead = is_dead(table->philos + i);
			pthread_mutex_unlock(&table->dead_mutex);
		}
		usleep(500);
	}
	return (NULL);
}
