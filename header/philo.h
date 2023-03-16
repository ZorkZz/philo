/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:57 by astachni          #+#    #+#             */
/*   Updated: 2023/03/16 15:29:39 by astachni         ###   ########.fr       */
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
	ssize_t		nb_fourr;
	t_mutex		mutex;
	t_mutex		*add_mutex;
}	t_philo;

t_philo	init_var(t_philo philo, char **strs);
int		ft_atoi(char *str);
int		ft_strlen(const char *str);

#endif