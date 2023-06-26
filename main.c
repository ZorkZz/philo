/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/26 21:36:26 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*txt1(void *data);

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
	ssize_t			i;
	ssize_t			time;
	t_the_philo		*philo_tmp;
	struct timeval	start;
	struct timeval	end;

	philo_tmp = (t_the_philo *)philo;
	time = 500;
	i = 0;
	time = philo_tmp->time_must_eat;
	while (i < time || time == -1)
	{
		gettimeofday(&start, NULL);
		printf("le philosophe %ld est en train de penser\n", \
		philo_tmp->nb_philo);
		printf("%0.8f--", philo_tmp->time_to_die * 0.0001);
		gettimeofday(&end, NULL);
		if ((end.tv_sec - start.tv_sec) \
			+ 0.000001 *(end.tv_usec - start.tv_usec) > philo_tmp->time_to_die * 0.0001)
				exit(1);
		pthread_mutex_lock(philo_tmp->l_fork);
		pthread_mutex_lock(philo_tmp->r_fork);
		printf("%0.8f\n", (end.tv_sec - start.tv_sec) \
			+ 0.000001 *(end.tv_usec - start.tv_usec));
		printf("le philosophe %ld est en train de manger\n", \
		philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_eat * 10);
		pthread_mutex_unlock(philo_tmp->l_fork);
		pthread_mutex_unlock(philo_tmp->r_fork);
		printf("le philosophe %ld est en train de dormir\n", \
		philo_tmp->nb_philo);
		usleep(philo_tmp->time_to_sleep * 10);
		i++;
		printf("%ld\n", time);
		}
	pthread_exit(NULL);
}
