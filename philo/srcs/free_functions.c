/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:34:21 by astachni          #+#    #+#             */
/*   Updated: 2023/06/30 14:20:18 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_philo(t_the_philo **the_philo)
{
	t_the_philo	*next;

	if (!the_philo)
		return ;
	next = *the_philo;
	while (next)
	{
		next = next->next;
		pthread_mutex_destroy(&(*the_philo)->last_eat_mutex);
		pthread_mutex_destroy(&(*the_philo)->is_finish_mutex);
		free(*the_philo);
		*the_philo = next;
	}
}

void	free_mutex(t_mutex **mutex)
{
	t_mutex	*next;

	if (!mutex)
		return ;
	next = *mutex;
	while (next)
	{
		next = next->next;
		pthread_mutex_destroy(&(*mutex)->fork);
		free(*mutex);
		*mutex = next;
	}
}

void	free_program(t_philo *philo)
{
	free_philo(&philo->the_philo);
	free_mutex(&philo->mutex);
	free(philo->philo);
	pthread_mutex_destroy(&philo->is_dead_mutex);
	pthread_mutex_destroy(&philo->write_mutex);
	free(philo);
}
