/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_born_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:55:45 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/21 18:09:51 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_usleep(size_t time)
{
	size_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void ft_printf(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_sem);
	printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, str);
	if (ft_strncmp(str, "died", 4))
		sem_post(philo->data->print_sem);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	fill_table(t_table *table, char **av, int ac)
{
	size_t	max_living;
	
	1 && (table->num_of_philo = ft_atoi(av[1]), table->time_to_die = ft_atoi(av[2]));
	1 && (table->time_to_eat = ft_atoi(av[3]), table->time_to_sleep = ft_atoi(av[4]));
	max_living = table->time_to_eat + table->time_to_sleep;
	if (ac == 6 && table->time_to_die > max_living && table->num_of_philo > 1)
		table->max_eat = ft_atoi(av[5]);
	else
		table->max_eat = -1;
	(sem_unlink("forks_sem"), sem_unlink("print_sem"));
	(sem_unlink("done_sem"), sem_unlink("dead_sem"));
	table->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0644, table->num_of_philo);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->dead_sem = sem_open("dead_sem", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->done_sem = sem_open("done_sem", O_CREAT | O_EXCL, 0644, 0);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
}

int	philo_life(int ac, char **av)
{
	t_philo	*philo;
	t_table	table;
	int		i;

	philo = malloc(sizeof(t_philo) * table.num_of_philo);
	if (!philo)
		return (1);
	1 && (fill_table(&table, av, ac), i = -1);
	while (++i < table.num_of_philo)
		1 && (philo[i].id = i + 1, philo[i].data = &table, philo[i].dead = 0);
	1 && (philo->dead = 0, philo->data->eat = 0, i = -1);
	while ((table.max_eat > 0 || table.max_eat == -1) && ++i < table.num_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			start_simulation(philo[i]);
	}
	if (table.max_eat > 0 || table.max_eat == -1)
		check_meals_death(philo);
	cleaner(philo);
	return (0);
}
