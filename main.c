/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/27 18:43:56 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*routine(void *philo);

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_the_philo		*the_philo;
	t_the_philo		*temp_the_philo;

	philo = NULL;
	if (ac > 1)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		philo->is_dead = -1;
		the_philo = philo->the_philo;
		while (philo->the_philo)
		{
			usleep(500);
			pthread_create(&philo->the_philo->thread, NULL,
				routine, philo);
			philo->the_philo = philo->the_philo->next;
		}
		temp_the_philo = the_philo;
		while (temp_the_philo)
		{
			pthread_join(temp_the_philo->thread, NULL);
			temp_the_philo = temp_the_philo->next;
		}
	}
	return (EXIT_SUCCESS);
}

void	*routine(void *philo)
{
	ssize_t			i;
	ssize_t			time;
	t_philo			*philo_tmp;
	t_the_philo		*the_philo;

	philo_tmp = (t_philo *)philo;
	the_philo = philo_tmp->the_philo;
	if (the_philo)
	{
		i = 0;
		time = philo_tmp->time_must_eat;
		usleep(400);
		philo_tmp->start = get_time();
		the_philo->last_eat = get_time() - philo_tmp->start;
		pthread_create(&the_philo->check_death, NULL, is_dead, philo_tmp);
		pthread_join(the_philo->check_death, NULL);
		while (i < time || time == -1)
		{
			printf("%ld %ld is thinking\n", \
			get_time() - the_philo->time, the_philo->nb_philo);
			pthread_mutex_lock(the_philo->l_fork);
			pthread_mutex_lock(the_philo->r_fork);
			printf("%ld %ld is eating\n", \
			get_time() - philo_tmp->start, the_philo->nb_philo);
			// if (philo_tmp->is_dead == 1)
			// 	exit (1);
			usleep(philo_tmp->time_to_eat * 10);
			the_philo->last_eat = get_time() -philo_tmp->start;
			pthread_mutex_unlock(the_philo->l_fork);
			pthread_mutex_unlock(the_philo->r_fork);
			printf("%ld %ld is slepping\n", \
			get_time() - philo_tmp->start, the_philo->nb_philo);
			usleep(philo_tmp->time_to_sleep * 10);
			i++;
		}
	}
	pthread_exit(NULL);
}
