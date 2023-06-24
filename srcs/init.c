/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/06/24 18:02:49 by astachni         ###   ########.fr       */
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
	if (nb_str > 2)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (NULL);
		philo->nb_philo = ft_atoi(strs[1]);
		philo->philo = NULL;
		philo->philo = malloc(sizeof(pthread_t) * philo->nb_philo + 1);
		if (!philo->philo)
			return (free(philo), NULL);
		philo->the_philo = NULL;
		init_the_philo(&philo->the_philo, philo->nb_philo, philo);
		if (!philo->the_philo)
			return (free(philo), free(philo->philo), NULL);
		init_mutex(&philo->mutex, philo->nb_philo);
		philo->the_philo = attr_fork(philo->the_philo, philo->mutex);
		printf("%p, %p\n", &philo->the_philo->r_fork, & philo->the_philo->l_fork);
	}
	return (philo);
}

t_the_philo	*attr_fork(t_the_philo *the_philo, t_mutex *mutex)
{
	t_the_philo	*temp;
	t_mutex		*temp_mutex;

	temp_mutex = mutex;
	temp = the_philo;
	printf("%p\n", &mutex->fork);
	while (the_philo && mutex)
	{
		the_philo->l_fork = mutex->fork;
		if (the_philo->next && mutex->next)
			the_philo->r_fork = mutex->next->fork;
		else if (!mutex->next)
			the_philo->r_fork = temp_mutex->fork;
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
		pthread_mutex_init(&new_node->fork, NULL);
		new_node->next = NULL;
		mutex_add_back(mutex, new_node);
		i++;
	}
}


void	init_the_philo(t_the_philo **the_philo, int nb_philo, t_philo *philo)
{
	t_the_philo	*new_node;
	int			i;

	i = 0;
	while (i < nb_philo)
	{
		new_node = malloc(sizeof(t_the_philo));
		new_node->thread = philo->philo[i];
		new_node->next = NULL;
		the_philo_add_back(the_philo, new_node);
		i++;
	}
}

void	free_philo(t_the_philo **the_philo)
{
	t_the_philo	*next;

	if (!the_philo)
		return ;
	next = *the_philo;
	while (next)
	{
		next = next->next;
		free(*the_philo);
		*the_philo = next;
	}
}
