/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:03:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/08/02 12:51:17 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->data->dead_sem);
		if (get_time() - philo->data->living_time >= philo->data->time_to_die)
		{
			ft_printf(philo, "died");
			sem_post(philo->data->dead_sem);
			exit(1);
		}
		if (philo->data->max_eat != -1 && \
philo->data->eat == philo->data->max_eat)
		{
			sem_post(philo->data->dead_sem);
			ft_usleep(500);
			exit(0);
		}
		sem_post(philo->data->dead_sem);
		usleep(100);
	}
}

void	check_meals_death(t_philo *philo)
{
	int		i;
	int		status;

	i = -1;
	while (++i < philo->data->num_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->data->num_of_philo)
				kill(philo[i].pid, SIGKILL);
			break ;
		}
	}
}

void	forks_handler(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	ft_printf(philo, "has taken a fork");
	sem_wait(philo->data->forks_sem);
	(ft_printf(philo, "has taken a fork"), ft_printf(philo, "is eating"));
	if (philo->data->max_eat != -1)
		philo->data->eat++;
	sem_wait(philo->data->dead_sem);
	philo->data->living_time = get_time();
	sem_post(philo->data->dead_sem);
	ft_usleep(philo->data->time_to_eat);
	(sem_post(philo->data->forks_sem), sem_post(philo->data->forks_sem));
}

void	start_simulation(t_philo philo)
{
	philo.data->living_time = philo.data->start;
	pthread_create(&philo.thread, NULL, monitoring, &philo);
	pthread_detach(philo.thread);
	if (philo.id % 2 == 0)
		ft_usleep(philo.data->time_to_eat);
	while (1)
	{
		forks_handler(&philo);
		ft_printf(&philo, "is sleeping");
		ft_usleep(philo.data->time_to_sleep);
		ft_printf(&philo, "is thinking");
	}
}
