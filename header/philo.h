/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:57 by astachni          #+#    #+#             */
/*   Updated: 2023/06/21 16:58:47 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				i;
}	t_mutex;

typedef struct s_philo
{
	pthread_t	*philo;
	ssize_t		nb_philo;
	ssize_t		*fork;
	ssize_t		time_to_eat;
	ssize_t		time_to_sleep;
	ssize_t		time_to_die;
	ssize_t		is_finish;
	t_mutex		mutex;
	t_mutex		*add_mutex;
}	t_philo;

//struct par philo

t_philo	*init_var(t_philo *philo, char **strs);
int		ft_atoi(char *str);
int		ft_strlen(const char *str);

#endif