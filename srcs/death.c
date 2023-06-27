/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:32:15 by astachni          #+#    #+#             */
/*   Updated: 2023/06/28 01:13:17 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*is_dead(void *philo)
{
	t_philo	*philo_tmp;

	philo_tmp = (t_philo *)philo;
	//printf("%p\n", philo_tmp->the_philo);
	while (philo_tmp->is_dead == -1)
	{
		if (philo_tmp->time_to_die < get_time() - philo_tmp->start - philo_tmp->the_philo->last_eat)
		{
			pthread_mutex_lock(&philo_tmp->is_dead_mutex);
			printf("%ld is dead", philo_tmp->the_philo->nb_philo);
			philo_tmp->is_dead = 1;
			pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
		}
	}
	pthread_exit(NULL);
}
