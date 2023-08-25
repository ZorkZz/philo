/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:55:01 by astachni          #+#    #+#             */
/*   Updated: 2023/08/25 16:01:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long int	call_action(t_the_philo *the_philo, long int i)
{
	think(the_philo, i);
	if (eat(the_philo) == 1)
		pthread_exit(NULL);
	if (sleep_philo(the_philo) == 1)
		pthread_exit(NULL);
	i++;
	return (i);
}
