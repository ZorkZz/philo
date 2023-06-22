/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/06/22 17:52:47 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

// t_philo	*init_var(t_philo *philo, char **strs)
// {
// 	philo = malloc(sizeof(t_philo));
// 	if (!philo)
// 		return (NULL);
// 	philo->nb_philo = ft_atoi(strs[1]);
// 	philo->time_to_die = ft_atoi(strs[2]);
// 	philo->philo = NULL;
// 	philo->philo = malloc(sizeof(pthread_t) * (philo->nb_philo + 1));
// 	if (!philo->philo)
// 	{
// 		free(philo);
// 		return (NULL);
// 	}
// 	return (philo);
// }

t_philo	*init_var(t_philo *philo, char **strs, int nb_str)
{
	if (nb_str > 3)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (NULL);
		philo->nb_philo = ft_atoi(strs[1]);
		philo->time_to_die = ft_atoi(strs[2]);
		philo->time_to_eat = ft_atoi(strs[3]);
		philo->philo = NULL;
		philo->philo = malloc(sizeof(pthread_t) * philo->nb_philo + 1);
		if (!philo->philo)
		{
			free(philo);
			return (NULL);
		}
	}
	return (philo);
}
