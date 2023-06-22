/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/22 17:57:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*txt1(void *data);

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	if (ac > 1)
	{
		philo = init_var(philo, av, ac);
		if (philo == NULL)
			return (1);
		philo->add_mutex = malloc(sizeof(t_mutex) + 1);
		if (!philo->add_mutex)
		{
			free(philo->philo);
			free(philo);
			return (1);
		}
		philo->add_mutex = &philo->mutex;
		philo->mutex.i = 3;
		printf("nb_philo: %zd\n", philo->nb_philo);
		pthread_mutex_init(&philo->mutex.mutex, NULL);
		while (i < philo->nb_philo)
		{
			pthread_create(&philo->philo[i], NULL, txt1,
				(void *)philo);
			i++;
		}
		i = 0;
		while (i < philo->nb_philo)
		{
			pthread_join(philo->philo[i], NULL);
			i++;
		}
		usleep(250);
		pthread_mutex_destroy(&philo->mutex.mutex);
	}
	free(philo->add_mutex);
	free(philo->philo);
	free(philo);
	return (0);
}

void	*txt1(void *philo)
{
	char	*str;
	int		i;
	t_philo	*philo_tmp;

	philo_tmp = (t_philo *)philo;
	i = 0;
	str = "le mutex cest magique\n";
	pthread_mutex_lock(&philo_tmp->mutex.mutex);
	while (i < ft_strlen(str))
		write(1, &str[i++], 1);
	pthread_mutex_unlock(&philo_tmp->mutex.mutex);
	pthread_exit(NULL);
}
