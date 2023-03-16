/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:19 by astachni          #+#    #+#             */
/*   Updated: 2023/03/15 15:31:58 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_philo	init_var(t_philo philo, char **strs)
{
	philo.nb_philo = ft_atoi(strs[1]);
	philo.nb_fourr = philo.nb_philo;
	philo.philo = NULL;
	philo.philo = malloc((philo.nb_philo * sizeof(pthread_t) + 1));
	return (philo);
}
