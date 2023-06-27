/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:57 by astachni          #+#    #+#             */
/*   Updated: 2023/06/27 16:16:23 by astachni         ###   ########.fr       */
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
	ssize_t				as_eat;
	u_int64_t			time;
	u_int64_t			last_eat;
	ssize_t				time_to_eat;
	ssize_t				time_to_sleep;
	ssize_t				time_to_die;
	ssize_t				time_must_eat;
	ssize_t				nb_philo;
	struct s_the_philo	*next;
}	t_the_philo;

typedef struct s_philo
{
	pthread_t	*philo;
	ssize_t		nb_philo;
	ssize_t		*fork;
	ssize_t		is_finish;
	ssize_t		time_to_eat;
	ssize_t		time_to_sleep;
	ssize_t		time_to_die;
	ssize_t		time_must_eat;
	t_mutex		*mutex;
	t_mutex		*add_mutex;
	t_the_philo	*the_philo;
}	t_philo;

t_philo		*init_var(t_philo *philo, char **strs, int nb_str);
int			ft_atoi(char *str);
int			ft_strlen(const char *str);
void		free_philo(t_the_philo **the_philo);
void		the_philo_add_back(t_the_philo **stack, t_the_philo *new_node);
void		mutex_add_back(t_mutex **stack, t_mutex *new_node);
u_int64_t	get_time(void);
#endif