/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/08/23 19:04:17 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void		free_philo(t_the_philo **the_philo);
void		init_the_philo(t_the_philo **the_philo,
				int nb_philo, t_philo *philo);
void		init_mutex(t_mutex **mutex, int nb_fork);
t_the_philo	*attr_fork(t_the_philo *the_philo, t_mutex *mutex);

t_philo	*init_var(t_philo *philo, char **strs, int nb_str)
{
	if (nb_str == 5 || nb_str == 6)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (NULL);
		philo = parsing(philo, strs, nb_str);
		if (!philo)
			return (NULL);
		philo->philo = NULL;
		philo->philo = malloc(sizeof(pthread_t) * philo->nb_philo);
		if (!philo->philo)
			return (free(philo), NULL);
		philo->the_philo = NULL;
		philo->begin = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_init(&philo->begin, NULL);
		init_the_philo(&philo->the_philo, philo->nb_philo, philo);
		if (!philo->the_philo)
			return (free(philo->philo), free(philo), NULL);
		philo->mutex = NULL;
		init_mutex(&philo->mutex, philo->nb_philo);
		if (!philo->mutex)
			return (free_program(philo), NULL);
		philo->the_philo = attr_fork(philo->the_philo, philo->mutex);
	}
	return (philo);
}

t_the_philo	*attr_fork(t_the_philo *the_philo, t_mutex *mutex)
{
	t_the_philo	*temp;
	t_mutex		*temp_mutex;

	temp_mutex = mutex;
	temp = the_philo;
	while (the_philo && mutex)
	{
		the_philo->l_fork = &(mutex->fork);
		if (the_philo->next && mutex->next)
			the_philo->r_fork = &mutex->next->fork;
		else if (!mutex->next)
			the_philo->r_fork = &temp_mutex->fork;
		the_philo = the_philo->next;
		mutex = mutex->next;
	}
	return (temp);
}

void	init_mutex(t_mutex **mutex, int nb_fork)
{
	t_mutex		*new_node;
	int			i;

	i = 0;
	while (i < nb_fork)
	{
		new_node = malloc(sizeof(t_mutex));
		new_node->fork = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_init(&new_node->fork, NULL);
		new_node->next = NULL;
		mutex_add_back(mutex, new_node);
		i++;
	}
}

t_the_philo	*add_mutex_philo(t_the_philo *new_node, t_philo *philo)
{
	new_node->time_must_eat = philo->time_must_eat;
	new_node->time_to_eat = philo->time_to_eat;
	new_node->time_to_sleep = philo->time_to_sleep;
	new_node->write_mutex = &philo->write_mutex;
	new_node->is_dead_mutex = &philo->is_dead_mutex;
	new_node->is_finish_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&new_node->is_finish_mutex, NULL);
	new_node->last_eat_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&new_node->last_eat_mutex, NULL);
	new_node->begin = &philo->begin;
	return (new_node);
}

void	init_the_philo(t_the_philo **the_philo, int nb_philo, t_philo *philo)
{
	t_the_philo	*new_node;
	int			i;

	i = 0;
	while (i < nb_philo)
	{
		new_node = malloc(sizeof(t_the_philo));
		if (!new_node)
		{
			free_philo(the_philo);
			*the_philo = NULL;
			return ;
		}
		new_node->thread = philo->philo[i];
		new_node->next = NULL;
		new_node = add_mutex_philo(new_node, philo);
		new_node->is_dead = -1;
		new_node->is_finish = -1;
		new_node->id_philo = i;
		new_node->nb_philo = philo->nb_philo;
		the_philo_add_back(the_philo, new_node);
		i++;
	}
}
