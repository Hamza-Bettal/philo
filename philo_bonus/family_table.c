/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:03:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/20 11:51:47 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_philo philo)
{
	if (philo.id % 2 == 0)
		ft_usleep(philo.data->time_to_eat);
	while (1)
	{
		sem_wait(philo.data->forks_sem);
		ft_printf(&philo, "has taken a fork");
		sem_wait(philo.data->forks_sem);
		ft_printf(&philo, "has taken a fork");
		ft_printf(&philo, "is eating");
		if (get_time() - philo.data->living_time >= philo.data->time_to_die)
		{
			sem_wait(philo.data->dead_sem);
			ft_printf(&philo, "died");
			sem_post(philo.data->done);
		}
		if (philo.num_of_meals != -1)
			philo.data->eat++;
		if (philo.data->max_eat != -1 && philo.data->eat == philo.data->max_eat)
			sem_post(philo.data->done);
		philo.data->living_time = get_time();
		ft_usleep(philo.data->time_to_eat);
		sem_post(philo.data->forks_sem);
		sem_post(philo.data->forks_sem);
		ft_printf(&philo, "is sleeping");
		ft_usleep(philo.data->time_to_sleep);
		ft_printf(&philo, "is thinking");
	}
}
