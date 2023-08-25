/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:52:37 by astachni          #+#    #+#             */
/*   Updated: 2023/08/25 13:32:20 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_atoi(char *str)
{
	int			i;
	int			is_neg;
	long int	nb;
	int			ii;

	i = 0;
	nb = 0;
	is_neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		is_neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	ii = i;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (i - ii > 10 || nb > 2147483647)
		return (-1);
	return (nb * is_neg);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) <= time_in_ms / 1000)
		usleep(1);
}

void	wait_time(t_the_philo *the_philo, t_philo *philo)
{
	if (!philo)
	{
		if (the_philo->id_philo == 0)
		{
			pthread_mutex_lock(the_philo->begin);
			usleep(50000 * (the_philo->nb_philo - the_philo->id_philo));
			pthread_mutex_unlock(the_philo->begin);
		}
		else
		{
			pthread_mutex_lock(the_philo->begin);
			pthread_mutex_unlock(the_philo->begin);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->begin);
		usleep(50 * philo->nb_philo);
		pthread_mutex_unlock(&philo->begin);
	}
}
