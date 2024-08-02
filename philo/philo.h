/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:48:09 by hbettal           #+#    #+#             */
/*   Updated: 2024/08/02 12:17:37 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				k;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_meals;
	int				num_of_philo;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_table;

struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*table;
	size_t			start;
	size_t			last_meal;
};

int		parse(char **av, int ac);
long	ft_atoi(char *str);
size_t	get_time(void);
void	ft_printf(t_philo *philo, char *str);
int		philo_birth(char **av, int ac);
void	start_simulation(t_philo *philo, t_table *table);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*monitoring(void *p);
int		is_dead(t_philo *dinner);

#endif