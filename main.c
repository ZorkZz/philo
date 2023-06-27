/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/28 01:14:50 by astachni         ###   ########.fr       */
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
		temp_the_philo = the_philo;
		while (philo->the_philo)
		{
			printf("%p\n", philo->the_philo);
			pthread_create(&philo->the_philo->thread, NULL,
				routine, philo);
			usleep(2000);
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
	long int			i;
	long int			time;
	t_philo			*philo_tmp;
	t_the_philo		*the_philo;

	philo_tmp = (t_philo *)philo;
	the_philo = philo_tmp->the_philo;
	printf("%p--\n", philo_tmp->the_philo);
	i = 0;
	time = philo_tmp->time_must_eat;
	usleep(5000);
	philo_tmp->start = get_time();
	the_philo->last_eat = 0;
	usleep(2000);
	pthread_create(&the_philo->check_death, NULL, is_dead, philo);
	pthread_join(the_philo->check_death, NULL);
	while (i < time || time == -1)
	{
		pthread_mutex_lock(&philo_tmp->is_dead_mutex);
		
		if (philo_tmp->is_dead == 1)
		{
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
		/*printf("%ld %ld is thinking\n", \
		get_time() - the_philo->time, the_philo->nb_philo);*/
		pthread_mutex_lock(the_philo->l_fork);
		pthread_mutex_lock(the_philo->r_fork);
		/*printf("%ld %ld is eating\n", \
		get_time() - philo_tmp->start, the_philo->nb_philo);*/
		pthread_mutex_lock(&philo_tmp->is_dead_mutex);
		//printf("--%ld--\n", philo_tmp->is_dead);
		if (philo_tmp->is_dead == 1)
			pthread_exit(NULL);
		pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
		usleep(philo_tmp->time_to_eat * 1000);
		the_philo->last_eat = get_time() - philo_tmp->start;
		pthread_mutex_unlock(the_philo->l_fork);
		pthread_mutex_unlock(the_philo->r_fork);
		pthread_mutex_lock(&philo_tmp->is_dead_mutex);
		//printf("--%ld--\n", philo_tmp->is_dead);
		if (philo_tmp->is_dead == 1)
			pthread_exit(NULL);
		pthread_mutex_unlock(&philo_tmp->is_dead_mutex);
		/*printf("%ld %ld is slepping\n", \
		get_time() - philo_tmp->start, the_philo->nb_philo);*/
		usleep(philo_tmp->time_to_sleep * 1000);
		printf("%ld, %ld\n", philo_tmp->time_to_die, get_time() - philo_tmp->start - the_philo->last_eat);
		i++;
	}
	pthread_exit(NULL);
}
