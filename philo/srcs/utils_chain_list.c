/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chain_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:38:09 by astachni          #+#    #+#             */
/*   Updated: 2023/06/24 17:39:08 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

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

t_the_philo	*ft_last_philo(t_the_philo *lst)
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
		ft_last_philo(*stack)->next = new_node;
	else
		*stack = new_node;
}
