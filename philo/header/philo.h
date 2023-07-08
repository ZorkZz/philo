/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:57 by astachni          #+#    #+#             */
/*   Updated: 2023/07/09 01:15:00 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_mutex
{
	pthread_mutex_t	fork;
	struct s_mutex	*next;
}	t_mutex;

typedef struct s_the_philo
{
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*write_mutex;
	pthread_mutex_t		*is_dead_mutex;
	pthread_mutex_t		is_finish_mutex;
	pthread_mutex_t		last_eat_mutex;
	pthread_mutex_t		*begin;
	long int			as_eat;
	long int			time;
	long int			*start;
	long int			time_to_sleep;
	long int			time_to_eat;
	long int			time_must_eat;
	long int			last_eat;
	long int			nb_philo;
	int					is_finish;
	int					is_dead;
	struct s_the_philo	*next;
}	t_the_philo;

typedef struct s_philo
{
	pthread_t		*philo;
	pthread_t		check_death;
	long int		nb_philo;
	long int		*fork;
	long int		is_finish;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		time_to_die;
	long int		time_must_eat;
	long int		is_dead;
	long int		start;
	pthread_mutex_t	begin;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	is_dead_mutex;
	t_mutex			*mutex;
	t_the_philo		*the_philo;
}	t_philo;

t_philo		*init_var(t_philo *philo, char **strs, int nb_str);
int			ft_atoi(char *str);
int			ft_strlen(const char *str);
void		free_philo(t_the_philo **the_philo);
void		the_philo_add_back(t_the_philo **stack, t_the_philo *new_node);
void		mutex_add_back(t_mutex **stack, t_mutex *new_node);
long int	get_time(void);
void		*is_dead(void *philo);
int			sleep_philo(t_the_philo *the_philo);
int			eat(t_the_philo *the_philo);
void		print_action(t_the_philo *the_philo, char *str);
t_philo		*parsing(t_philo *philo, char **strs, int nb_str);
void		free_program(t_philo *philo);
void		ft_usleep(long int time_in_ms);
void		wait_time(t_the_philo *the_philo, t_philo *philo);
#endif