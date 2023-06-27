/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:32:15 by astachni          #+#    #+#             */
/*   Updated: 2023/06/27 17:44:52 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*is_dead(void *philo)
{
	t_philo	*philo_tmp;

	philo_tmp = (t_philo *)philo;
	while (1)
	{
		if (philo_tmp->the_philo->last_eat > (get_time() - philo_tmp->the_philo->time))
		{
			pthread_mutex_lock(&philo_tmp->is_dead_mutex);
			philo_tmp->is_dead = 1;
			pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
		}
	}
	pthread_exit(NULL);
}
