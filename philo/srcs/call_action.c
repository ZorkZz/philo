/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:55:01 by astachni          #+#    #+#             */
/*   Updated: 2023/08/27 17:08:23 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long int	call_action(t_the_philo *the_philo, long int i)
{
	if (i > 0 || (i == 0 && ((the_philo->id_philo % 2 != 0
					&& the_philo->nb_philo % 2 == 0)
				|| (the_philo->nb_philo % 2 != 0))))
		think(the_philo, i);
	if (eat(the_philo) == 1)
		pthread_exit(NULL);
	if (sleep_philo(the_philo) == 1)
		pthread_exit(NULL);
	i++;
	return (i);
}
