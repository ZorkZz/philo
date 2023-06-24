/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/24 18:02:00 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*txt1(void *data);

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_the_philo	*the_philo;
	int			i;

	i = 0;
	philo = NULL;
	if (ac > 1)
	{
		philo = init_var(philo, av, ac);
		the_philo = philo->the_philo;
		if (philo == NULL)
			return (EXIT_FAILURE);
		//philo->mutex = malloc(sizeof(t_mutex));
		// if (!philo->mutex)
		// {
		// 	free(philo->philo);
		// 	free(philo);
		// 	return (EXIT_FAILURE);
		// }
		printf("nb_philo: %zd\n", philo->nb_philo);
		while (i < philo->nb_philo)
		{
			pthread_create(&philo->the_philo->thread, NULL, txt1,
				philo->the_philo);
			i++;
		}
		i = 0;
		while (i < philo->nb_philo)
		{
			pthread_join(philo->the_philo->thread, NULL);
			i++;
		}
		usleep(250);
		free_philo(&philo->the_philo);
		free(philo->philo);
		free(philo);
	}
	return (EXIT_SUCCESS);
}

void	*txt1(void *philo)
{
	char		*str;
	int			i;
	t_the_philo	*philo_tmp;

	philo_tmp = (t_the_philo *)philo;
	i = 0;
	str = "le mutex cest magique\n";
	pthread_mutex_lock(&philo_tmp->l_fork);
	pthread_mutex_lock(&philo_tmp->r_fork);
	while (i < ft_strlen(str))
		write(1, &str[i++], 1);
	pthread_mutex_unlock(&philo_tmp->l_fork);
	pthread_mutex_unlock(&philo_tmp->r_fork);
	pthread_exit(NULL);
}
