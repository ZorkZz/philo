/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:32:15 by astachni          #+#    #+#             */
/*   Updated: 2023/06/29 18:07:29 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	dead_philo(t_the_philo	**the_philo);

void	*is_dead(void *philo)
{
	t_philo		*philo_tmp;
	t_the_philo	*the_philo;
	t_the_philo	*the_philo_tmp;

	philo_tmp = (t_philo *)philo;
	the_philo = philo_tmp->the_philo;
	while (philo_tmp->is_dead == -1)
	{
		the_philo_tmp = the_philo;
		while (the_philo_tmp)
		{
			if (philo_tmp->time_to_die < get_time() - the_philo_tmp->start - \
				the_philo_tmp->last_eat)
			{
				pthread_mutex_lock(&philo_tmp->is_dead_mutex);
				print_action(the_philo_tmp, "is dead");
				dead_philo(&the_philo);
				pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
				pthread_exit(NULL);
			}
			the_philo_tmp = the_philo_tmp->next;
		}
	}
	pthread_exit(NULL);
}

void	dead_philo(t_the_philo	**the_philo)
{
	while (the_philo && *the_philo)
	{
		//pthread_detach((*the_philo)->thread);
		(*the_philo)->is_dead = 1;
		(*the_philo) = (*the_philo)->next;
	}	
}
