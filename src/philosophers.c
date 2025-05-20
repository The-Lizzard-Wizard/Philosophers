/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:07 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/20 17:34:38 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../inc/philosophers.h"
#include <pthread.h>

void	pars(char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("nb_philo : %u\nttd : %u\ntte : %u\ntts : %u\n", data->nb_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
}

void	*philo_routin(void	*philo)
{
	pthread_t	self_tid;
	(void)philo;

	self_tid = pthread_self();
	printf("je suis un phiolosophe et j'existe %ld\n", self_tid);
	return (NULL);
}

void	init_philo(t_data *data)
{
	unsigned int	i;

	data->philo_list = malloc(sizeof(t_philo) * data->nb_philo);
	i = -1;
	while (++i < data->nb_philo)
	{
		printf("pute %u\n", i);
		pthread_create(&data->philo_list[i].philo_tid, NULL, &philo_routin, &data->philo_list[i]);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	pars(argv, data);
	init_philo(data);
	return (EXIT_SUCCESS);
}
