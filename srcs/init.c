/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/06/24 17:25:20 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void		free_philo(t_the_philo **the_philo);
void		init_the_philo(t_the_philo **the_philo, int nb_philo);

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
		init_the_philo(&philo->the_philo, philo->nb_philo);
		if (!philo->the_philo)
			return (free(philo), free(philo->philo), NULL);
	}
	return (philo);
}

t_mutex	*ft_last_mutex(t_mutex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	mutex_add_back(t_mutex **stack, t_mutex *new_node)
{
	if (!stack)
		return ;
	if (*stack)
		ft_last_mutex(*stack)->next = new_node;
	else
		*stack = new_node;
}

void	init_mutex(t_mutex **mutex, int nb_fork)
{
	t_mutex	*new_node;
	int		i;

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

t_the_philo	*ft_last_cmd(t_the_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	the_philo_add_back(t_the_philo **stack, t_the_philo *new_node)
{
	if (!stack)
		return ;
	if (*stack)
		ft_last_cmd(*stack)->next = new_node;
	else
		*stack = new_node;
}

void	init_the_philo(t_the_philo **the_philo, int nb_philo)
{
	t_the_philo	*new_node;
	int			i;

	i = 0;
	while (i < nb_philo)
	{
		new_node = malloc(sizeof(t_the_philo));
		new_node->next = NULL;
		new_node->thread = 150;
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
