/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:32:15 by astachni          #+#    #+#             */
/*   Updated: 2023/07/09 01:15:38 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	dead_philo(t_the_philo	**the_philo);
void	dead_condition(t_the_philo *the_philo, \
		t_the_philo *the_philo_tmp, t_philo *philo_tmp);

void	*is_dead(void *philo)
{
	t_philo		*philo_tmp;
	t_the_philo	*the_philo;
	t_the_philo	*the_philo_tmp;

	philo_tmp = (t_philo *)philo;
	the_philo = philo_tmp->the_philo;
	wait_time(NULL, philo_tmp);
	pthread_mutex_lock(&the_philo->last_eat_mutex);
	the_philo->last_eat = 0;
	pthread_mutex_unlock(&the_philo->last_eat_mutex);
	while (philo_tmp->is_dead == -1)
	{
		the_philo_tmp = the_philo;
		while (the_philo_tmp)
		{
			pthread_mutex_lock(&the_philo_tmp->last_eat_mutex);
			if (philo_tmp->time_to_die < get_time() - *the_philo_tmp->start - \
				the_philo_tmp->last_eat)
				dead_condition(the_philo, the_philo_tmp, philo_tmp);
			pthread_mutex_unlock(&the_philo_tmp->last_eat_mutex);
			the_philo_tmp = the_philo_tmp->next;
		}
	}
	pthread_exit(NULL);
}

void	dead_condition(t_the_philo *the_philo, \
		t_the_philo *the_philo_tmp, t_philo *philo_tmp)
{
	pthread_mutex_unlock(&the_philo_tmp->last_eat_mutex);
	pthread_mutex_lock(&philo_tmp->is_dead_mutex);
	pthread_mutex_lock(&the_philo_tmp->is_finish_mutex);
	if (the_philo_tmp->is_finish == -1)
		print_action(the_philo_tmp, "is dead");
	pthread_mutex_unlock(&the_philo_tmp->is_finish_mutex);
	dead_philo(&the_philo);
	pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
	pthread_exit(NULL);
}

void	dead_philo(t_the_philo **the_philo)
{
	while (the_philo && *the_philo)
	{
		(*the_philo)->is_dead = 1;
		(*the_philo) = (*the_philo)->next;
	}	
}
