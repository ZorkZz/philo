/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/30 15:25:09 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void		*routine(void *philo);
void		start_routine(t_the_philo *the_philo);
void		join_routine(t_the_philo *the_philo);
t_the_philo	*order_fork(t_the_philo *the_philo);

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_the_philo		*the_philo;

	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		philo->is_dead = -1;
		the_philo = philo->the_philo;
		while (the_philo)
		{
			the_philo = order_fork(the_philo);
			the_philo = the_philo->next;
		}
		the_philo = philo->the_philo;
		start_routine(the_philo);
		pthread_create(&philo->check_death, NULL, is_dead, philo);
		pthread_join(philo->check_death, NULL);
		join_routine(the_philo);
		free_program(philo);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
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
	i = 0;
	time = the_philo->time_must_eat;
	pthread_mutex_lock(&the_philo->last_eat_mutex);
	the_philo->last_eat = 0;
	pthread_mutex_unlock(&the_philo->last_eat_mutex);
	while ((i < time || time == -1) && the_philo->is_dead == -1)
	{
		print_action(the_philo, "is thinking");
		if (eat(the_philo) == 1)
			pthread_exit(NULL);
		if (sleep_philo(the_philo) == 1)
			pthread_exit(NULL);
		i++;
	}
	pthread_mutex_lock(&the_philo->is_finish_mutex);
	the_philo->is_finish = 1;
	pthread_mutex_unlock(&the_philo->is_finish_mutex);
	pthread_exit(NULL);
}

t_the_philo	*order_fork(t_the_philo *the_philo)
{
	pthread_mutex_t	*temp;

	if (the_philo->nb_philo % 2 == 0)
	{
		temp = the_philo->l_fork;
		the_philo->l_fork = the_philo->r_fork;
		the_philo->r_fork = temp;
	}
	return (the_philo);
}
