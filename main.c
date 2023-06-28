/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/28 17:38:41 by astachni         ###   ########.fr       */
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
	if (ac > 3)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		philo->is_dead = -1;
		the_philo = philo->the_philo;
		temp_the_philo = the_philo;
		pthread_create(&philo->check_death, NULL, is_dead, philo);
		pthread_join(philo->check_death, NULL);
		while (temp_the_philo)
		{
			pthread_create(&temp_the_philo->thread, NULL,
				routine, temp_the_philo);
			temp_the_philo = temp_the_philo->next;
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
	long int			i;
	long int			time;
	t_the_philo		*the_philo;

	pthread_mutex_lock(the_philo->start_simu);
	pthread_mutex_unlock(the_philo->start_simu);
	the_philo = (t_the_philo *)philo;
	i = 0;
	time = the_philo->time_must_eat;
	the_philo->start = get_time();
	the_philo->last_eat = 0;
	while (i < time || time == -1)
	{
		printf("%ld %ld is thinking\n", get_time() - the_philo->start, the_philo->nb_philo);
		pthread_mutex_lock(the_philo->l_fork);
		printf("%ld %ld take a fork\n", get_time() - the_philo->start, the_philo->nb_philo);
		pthread_mutex_lock(the_philo->r_fork);
		printf("%ld %ld take a fork\n", get_time() - the_philo->start, the_philo->nb_philo);
		printf("%ld %ld is eating\n", get_time() - the_philo->start, the_philo->nb_philo);
		usleep(the_philo->time_to_eat * 1000);
		the_philo->last_eat = get_time() - the_philo->start;
		pthread_mutex_unlock(the_philo->l_fork);
		pthread_mutex_unlock(the_philo->r_fork);
		printf("%ld %ld is sleeping\n", get_time() - the_philo->start, the_philo->nb_philo);
		usleep(the_philo->time_to_sleep * 1000);
		i++;
	}
	pthread_exit(NULL);
}
