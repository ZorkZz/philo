/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/25 17:35:20 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*txt1(void *data);

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_the_philo	*the_philo;
	t_the_philo	*temp_the_philo;

	philo = NULL;
	if (ac > 1)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (EXIT_FAILURE);
		the_philo = philo->the_philo;
		printf("nb_philo: %zd\n", philo->nb_philo);
		temp_the_philo = the_philo;
		while (temp_the_philo)
		{
			pthread_create(&temp_the_philo->thread, NULL, txt1, temp_the_philo);
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

void	*txt1(void *philo)
{
	int			i;
	t_the_philo	*philo_tmp;

	philo_tmp = (t_the_philo *)philo;
	i = 0;
	while (i < 18)
	{
		printf("le philosophe %ld\n est en train de penser\n", philo_tmp->nb_philo);
		pthread_mutex_lock(philo_tmp->l_fork);
		pthread_mutex_lock(philo_tmp->r_fork);
		printf("le philosophe %ld\n est en train de manger\n", philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_eat);
		pthread_mutex_unlock(philo_tmp->l_fork);
		pthread_mutex_unlock(philo_tmp->r_fork);
		printf("le philosophe %ld\n est en train de dormir\n", philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_sleep);
		i++;
	}
	pthread_exit(NULL);
}
