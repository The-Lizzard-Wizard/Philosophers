/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:07 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/18 17:19:50 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

long int	get_time(long int first_milisec)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000 - first_milisec));
}

int	start_philo(t_data *data)
{
	if (init_table(data) == 0)
		return (0);
	return (1);
}

int	stop_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (data->philo_list)
	{
		while (i < data->nb_philo)
		{
			pthread_join(data->philo_list[i].philo_tid, NULL);
			i++;
		}
		free_philos(data->philo_list, data->nb_philo);
	}
	destroy_fork(data->someoneide);
	return (1);
}

int	main(int argc, char **argv)

{
	t_data	*data;

	if (argc != 6)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	pars(argv, data);
	if (start_philo(data) == 1)
		stop_philo(data);
	free(data);
	return (EXIT_SUCCESS);
}
