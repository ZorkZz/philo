/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/27 16:36:11 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*routine(void *philo);

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_the_philo		*the_philo;
	t_the_philo		*temp_the_philo;
	t_timeval		start;

	philo = NULL;
	if (ac > 1)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		the_philo = philo->the_philo;
		temp_the_philo = the_philo;
		gettimeofday(&start, NULL);
		while (temp_the_philo)
		{
			pthread_create(&temp_the_philo->thread, NULL, routine, temp_the_philo);
			temp_the_philo = temp_the_philo->next;
		}
		temp_the_philo = the_philo;
		while (temp_the_philo)
		{
			pthread_join(temp_the_philo->thread, NULL);
			temp_the_philo = temp_the_philo->next;
		}
		free_philo(&philo->the_philo);
		free(philo->philo);
		free(philo);
	}
	return (EXIT_SUCCESS);
}

void	*routine(void *philo)
{
	ssize_t			i;
	ssize_t			time;
	t_the_philo		*philo_tmp;

	philo_tmp = (t_the_philo *)philo;
	i = 0;
	time = philo_tmp->time_must_eat;
	while (i < time || time == -1)
	{
		printf("%ld %ld is thinking\n", \
		get_time() - philo_tmp->time, philo_tmp->nb_philo);
		pthread_mutex_lock(philo_tmp->l_fork);
		pthread_mutex_lock(philo_tmp->r_fork);
		printf("%ld %ld is eating\n", \
		get_time() - philo_tmp->time, philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_eat * 10);
		pthread_mutex_unlock(philo_tmp->l_fork);
		pthread_mutex_unlock(philo_tmp->r_fork);
		printf("%ld %ld is slepping\n", \
		get_time() - philo_tmp->time, philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_sleep * 10);
		i++;
	}
	pthread_exit(NULL);
}
