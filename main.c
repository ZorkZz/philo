/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:28:29 by astachni          #+#    #+#             */
/*   Updated: 2023/03/14 14:02:06 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*txt1(void *data);
void	*txt2(void *data);

int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;
	t_mutex		mut;
	t_mutex		*el_mutex;

	el_mutex = malloc((sizeof(t_mutex) * 1));
	el_mutex = &mut;
	mut.i = 3;
	pthread_mutex_init(&mut.mutex, NULL);
	pthread_create(&t1, NULL, txt1, (void *)el_mutex);
	pthread_create(&t2, NULL, txt2, (void *)el_mutex);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}

void	*txt1(void *mutex)
{
	char	*str;
	int		i;
	t_mutex	*el_mutex;

	el_mutex = (t_mutex *)mutex;
	i = 0;
	str = "la bite cest delicieux\n";
	pthread_mutex_lock(&el_mutex->mutex);
	while (i < 23)
	{
		fprintf(stderr, "%c", str[i++]);
		usleep(10000);
	}
	pthread_mutex_unlock(&el_mutex->mutex);
	pthread_exit(NULL);
}

void	*txt2(void *mutex)
{
	char	*str;
	int		i;
	t_mutex	*el_mutex;

	el_mutex = (t_mutex *)mutex;
	i = 0;
	str = "finalement cest pas si fou la bite\n";
	pthread_mutex_lock(&el_mutex->mutex);
	while (i < 35)
	{
		fprintf(stderr, "%c", str[i++]);
		usleep(10000);
	}
	pthread_mutex_unlock(&el_mutex->mutex);
	pthread_exit(NULL);
}
