/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:26:47 by astachni          #+#    #+#             */
/*   Updated: 2023/06/29 15:35:34 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_action(t_the_philo *the_philo, char *str)
{
	pthread_mutex_lock(the_philo->write_mutex);
	printf("%ld %ld %s\n", get_time() - the_philo->start,
		the_philo->nb_philo, str);
	pthread_mutex_unlock(the_philo->write_mutex);
}

int	eat(t_the_philo *the_philo)
{
	pthread_mutex_lock(the_philo->l_fork);
	pthread_mutex_lock(the_philo->is_dead_mutex);
	if (the_philo->is_dead != -1)
	{
		pthread_mutex_lock(the_philo->l_fork);
		pthread_mutex_lock(the_philo->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(the_philo->is_dead_mutex);
	print_action(the_philo, "take a fork");
	pthread_mutex_lock(the_philo->r_fork);
	pthread_mutex_lock(the_philo->is_dead_mutex);
	if (the_philo->is_dead != -1)
	{
		pthread_mutex_unlock(the_philo->l_fork);
		pthread_mutex_unlock(the_philo->r_fork);
		pthread_mutex_unlock(the_philo->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(the_philo->is_dead_mutex);
	print_action(the_philo, "take a fork");
	print_action(the_philo, "is eating");
	usleep(the_philo->time_to_eat * 1000);
	the_philo->last_eat = get_time() - the_philo->start;
	pthread_mutex_unlock(the_philo->l_fork);
	pthread_mutex_unlock(the_philo->r_fork);
	return (0);
}

int	sleep_philo(t_the_philo *the_philo)
{
	pthread_mutex_lock(the_philo->is_dead_mutex);
	if (the_philo->is_dead != -1)
		return (1);
	pthread_mutex_unlock(the_philo->is_dead_mutex);
	print_action(the_philo, "is sleeping");
	usleep(the_philo->time_to_sleep * 1000);
	pthread_mutex_lock(the_philo->is_dead_mutex);
	if (the_philo->is_dead != -1)
	{
		pthread_mutex_unlock(the_philo->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(the_philo->is_dead_mutex);
	return (0);
}
