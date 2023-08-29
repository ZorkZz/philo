/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:26:47 by astachni          #+#    #+#             */
/*   Updated: 2023/08/29 16:44:48 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	unlock_mutex(t_the_philo *the_philo, int i, int j);

void	print_action(t_the_philo *the_philo, char *str, int code)
{
	if (code != 4)
	{
		pthread_mutex_lock(the_philo->is_dead_mutex);
		if (the_philo->is_dead != -1)
			return (unlock_mutex(the_philo, code, 0));
		pthread_mutex_unlock(the_philo->is_dead_mutex);
	}
	pthread_mutex_lock(the_philo->write_mutex);
	if (code != 4)
	{
		pthread_mutex_lock(the_philo->is_dead_mutex);
		if (the_philo->is_dead != -1)
			return (unlock_mutex(the_philo, code, 1));
		pthread_mutex_unlock(the_philo->is_dead_mutex);
	}
	printf("%ld %ld %s\n", get_time()
		- *the_philo->start, the_philo->id_philo + 1, str);
	pthread_mutex_unlock(the_philo->write_mutex);
}

void	unlock_mutex(t_the_philo *the_philo, int i, int j)
{
	if (i == 1)
		pthread_mutex_unlock(the_philo->l_fork);
	else if (i == 2)
	{
		pthread_mutex_unlock(the_philo->l_fork);
		pthread_mutex_unlock(the_philo->r_fork);
	}
	if (j == 1)
		pthread_mutex_unlock(the_philo->write_mutex);
	pthread_mutex_unlock(the_philo->is_dead_mutex);
	pthread_exit(NULL);
}

int	eat(t_the_philo *the_philo)
{
	pthread_mutex_lock(the_philo->l_fork);
	print_action(the_philo, "has taken a fork", 1);
	pthread_mutex_lock(the_philo->r_fork);
	print_action(the_philo, "has taken a fork", 2);
	print_action(the_philo, "is eating", 2);
	pthread_mutex_lock(&the_philo->last_eat_mutex);
	the_philo->last_eat = get_time() - *the_philo->start;
	pthread_mutex_unlock(&the_philo->last_eat_mutex);
	usleep(the_philo->time_to_eat * 1000);
	pthread_mutex_unlock(the_philo->l_fork);
	pthread_mutex_unlock(the_philo->r_fork);
	return (0);
}

int	sleep_philo(t_the_philo *the_philo)
{
	print_action(the_philo, "is sleeping", 3);
	usleep(the_philo->time_to_sleep * 1000);
	return (0);
}

int	think(t_the_philo *the_philo, long int i)
{
	int	usleep_time;

	usleep_time = the_philo->time_to_sleep;
	if (i == 0 && the_philo->id_philo % 2 == 0 && the_philo->nb_philo % 2 == 0)
	{
		print_action(the_philo, "is thinking", 3);
		usleep(100 * the_philo->nb_philo);
	}
	else if (i > 0 && the_philo->nb_philo % 2 != 0)
	{
		if (the_philo->time_to_eat > the_philo->time_to_sleep)
			usleep_time = the_philo->time_to_eat;
		print_action(the_philo, "is thinking", 3);
		usleep(usleep_time * 1000);
	}
	else if (i == 0 && the_philo->id_philo % 2 != 0
		&& the_philo->nb_philo % 2 == 0)
		print_action(the_philo, "is thinking", 3);
	else if (i == 0 && the_philo->nb_philo % 2 != 0)
		print_action(the_philo, "is thinking", 3);
	else if (i > 0)
		print_action(the_philo, "is thinking", 3);
	return (0);
}
