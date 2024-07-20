/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_born_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:55:45 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/20 11:57:30 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_usleep(size_t time)
{
	size_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(1000);
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

void	fill_table(t_table *table, char **av)
{
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->max_eat = ft_atoi(av[5]);
	else
		table->max_eat = -1;
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("dead_sem");
	sem_unlink("done");
	table->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0644, table->num_of_philo);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->dead_sem = sem_open("dead_sem", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
	table->done = sem_open("done", O_CREAT | O_EXCL, 0644, 0);
	if (table->forks_sem == SEM_FAILED)
		(printf("sem_open fail"), exit(1));
}

int	philo_life(int ac, char **av)
{
	t_philo	*philo;
	t_table	table;
	int		i;
	
	fill_table(&table, av);
	philo = malloc(sizeof(t_philo) * table.num_of_philo);
	i = -1;
	while (++i < table.num_of_philo)
	{
		1 && (philo[i].id = i + 1, philo[i].data = &table, philo[i].dead = 0);
		if (ac == 6)
			philo[i].num_of_meals = ft_atoi(av[5]);
		else
			philo[i].num_of_meals = -1;
	}
	philo->dead = 0;
	philo->data->eat = 0;
	i = -1;
	table.start = get_time();
	table.living_time = get_time();
	while (++i < table.num_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			start_simulation(philo[i]);
	}
	if (philo->num_of_meals != -1)
	{
		i = -1;
		printf("hererererre\n");
		while (++i < table.num_of_philo)
			sem_wait(table.done);
	}
	else
		sem_wait(table.done);
	i = -1;
	while (++i < philo->data->num_of_philo)
		kill(philo[i].pid, SIGKILL);
	return (0);
}
