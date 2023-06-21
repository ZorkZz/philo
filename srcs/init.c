/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/06/21 16:55:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_philo	*init_var(t_philo *philo, char **strs)
{
	philo = malloc(sizeof(philo));
	if (!philo)
		return (NULL);
	philo->nb_philo = ft_atoi(strs[1]);
	philo->philo = NULL;
	philo->philo = malloc(sizeof(pthread_t) * philo->nb_philo + 1);
	if (!philo->philo)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
