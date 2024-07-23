/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:03:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/22 14:50:57 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_meals_death(t_philo *philo)
{
	int		i;

	if (philo->data->max_eat != -1)
	{
		i = -1;
		while (++i < philo->data->num_of_philo)
			sem_wait(philo->data->done_sem);
		printf("all philos ate %d times\n", philo->data->max_eat);
	}
	else
		sem_wait(philo->data->done_sem);
	i = -1;
	while (++i < philo->data->num_of_philo)
		kill(philo[i].pid, SIGTERM);
}

void	forks_handler(t_philo philo)
{
	sem_wait(philo.data->forks_sem);
	ft_printf(&philo, "has taken a fork");
	if (philo.data->num_of_philo == 1)
	{
		ft_usleep(philo.data->time_to_die, philo);
		(ft_printf(&philo, "died"), sem_post(philo.data->done_sem));
	}
	sem_wait(philo.data->forks_sem);
	(ft_printf(&philo, "has taken a fork"), ft_printf(&philo, "is eating"));
	if (philo.data->max_eat != -1)
		philo.data->eat++;
	if (philo.data->max_eat != -1 && philo.data->eat == philo.data->max_eat)
		sem_post(philo.data->done_sem);
	philo.data->living_time = get_time();
	ft_usleep(philo.data->time_to_eat, philo);
	(sem_post(philo.data->forks_sem), sem_post(philo.data->forks_sem));
}

void	start_simulation(t_philo philo)
{
	philo.data->start = get_time();
	philo.data->living_time = philo.data->start;
	if (philo.id % 2 == 0)
		ft_usleep(philo.data->time_to_eat, philo);
	while (1)
	{
		forks_handler(philo);
		ft_printf(&philo, "is sleeping");
		ft_usleep(philo.data->time_to_sleep, philo);
		ft_printf(&philo, "is thinking");
	}
}
