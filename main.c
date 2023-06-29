/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/29 15:52:39 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*routine(void *philo);
void	start_routine(t_the_philo *the_philo);
void	join_routine(t_the_philo *the_philo);

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_the_philo		*the_philo;

	philo = NULL;
	if (ac > 3)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		philo->is_dead = -1;
		the_philo = philo->the_philo;
		start_routine(the_philo);
		pthread_create(&philo->check_death, NULL, is_dead, philo);
		pthread_join(philo->check_death, NULL);
		join_routine(the_philo);
	}
	return (EXIT_SUCCESS);
}

void	join_routine(t_the_philo *the_philo)
{
	while (the_philo)
	{
		pthread_join(the_philo->thread, NULL);
		the_philo = the_philo->next;
	}
}

void	start_routine(t_the_philo *the_philo)
{
	while (the_philo)
	{
		the_philo->start = get_time();
		pthread_create(&the_philo->thread, NULL,
			routine, the_philo);
		the_philo = the_philo->next;
	}
}

void	*routine(void *philo)
{
	long int	i;
	long int	time;
	t_the_philo	*the_philo;

	the_philo = (t_the_philo *)philo;
	the_philo->start = get_time();
	pthread_mutex_lock(the_philo->write_mutex);
	pthread_mutex_unlock(the_philo->write_mutex);
	i = 0;
	time = the_philo->time_must_eat;
	the_philo->last_eat = 0;
	while (i < time || time == -1)
	{
		print_action(the_philo, "is thinking");
		if (eat(the_philo) == 1)
			pthread_exit(NULL);
		if (sleep_philo(the_philo) == 1)
			pthread_exit(NULL);
		i++;
	}
	pthread_exit(NULL);
}
