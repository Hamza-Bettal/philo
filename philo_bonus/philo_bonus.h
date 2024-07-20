/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:06:05 by hbettal           #+#    #+#             */
/*   Updated: 2024/07/20 11:54:43 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_table
{
	int				num_of_philo;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	size_t			living_time;
	size_t		start;
	int				eat;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*done;
} t_table;

typedef struct s_philo
{
	int			id;
	int			num_of_meals;
	pid_t		pid;
	t_table		*data;
	int			dead;
} t_philo;


int			parsing(int ac, char **av);
long		ft_atoi(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int 		philo_life(int ac, char **av);
size_t		get_time(void);
void		ft_usleep(size_t time);
void		ft_printf(t_philo *philo, char *str);
void		start_simulation(t_philo philo);
void		*close_kill(void *arg);
void		*wait_dead(void *prog);

#endif