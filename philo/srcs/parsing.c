/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:40:25 by astachni          #+#    #+#             */
/*   Updated: 2023/06/30 14:20:50 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	verif_strs(char **strs, int nb_str);

t_philo	*parsing(t_philo *philo, char **strs, int nb_str)
{
	if (verif_strs(strs, nb_str) == 1)
		return (free(philo), NULL);
	philo->nb_philo = ft_atoi(strs[1]);
	philo->time_to_die = ft_atoi(strs[2]);
	philo->time_to_eat = ft_atoi(strs[3]);
	philo->time_to_sleep = ft_atoi(strs[4]);
	if (nb_str == 6)
		philo->time_must_eat = ft_atoi(strs[5]);
	else
		philo->time_must_eat = -1;
	philo->is_dead_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&philo->is_dead_mutex, NULL);
	philo->write_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&philo->write_mutex, NULL);
	return (philo);
}

int	is_nb(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	verif_strs(char **strs, int nb_str)
{
	int	i;

	i = 1;
	while (i < nb_str)
	{
		if (is_nb(strs[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}