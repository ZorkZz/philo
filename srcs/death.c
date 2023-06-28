/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:32:15 by astachni          #+#    #+#             */
/*   Updated: 2023/06/28 16:29:36 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	wait_philos(t_philo	*philo);
void	*is_dead(void *philo)
{
	t_philo		*philo_tmp;
	t_the_philo	*the_philo;
	t_the_philo	*the_philo_tmp;

	philo_tmp = (t_philo *)philo;
	wait_philos(philo_tmp);
	the_philo = philo_tmp->the_philo;
	printf("%p\n", the_philo->next);
	while (philo_tmp->is_dead == -1)
	{
		the_philo_tmp = the_philo;
		while (the_philo_tmp)
		{
			printf("%ld, %ld\n", philo_tmp->time_to_die, get_time() - the_philo_tmp->start - the_philo_tmp->last_eat);
			if (philo_tmp->time_to_die < get_time() - the_philo_tmp->start - the_philo_tmp->last_eat)
			{
				pthread_mutex_lock(&philo_tmp->is_dead_mutex);
				printf("%ld is dead", philo_tmp->the_philo->nb_philo);
				philo_tmp->is_dead = 1;
				exit(1);
				pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
			}
			the_philo_tmp = the_philo_tmp->next;
		}
	}
	pthread_exit(NULL);
}

void	wait_philos(t_philo	*philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo->start_simu);
	while (++i < 10)
		usleep(1000);
	pthread_mutex_unlock(&philo->start_simu);
	return ;
}