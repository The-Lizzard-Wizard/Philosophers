/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:07 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/06 16:11:22 by gchauvet         ###   ########.fr       */
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
	init_table(data);
	return (0);
}

int	stop_philo(t_data *data)
{
	unsigned int i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo_list[i].philo_tid, NULL);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)

{
	t_data *data;

	if (argc != 5)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	pars(argv, data);
	start_philo(data);
	stop_philo(data);
	return (EXIT_SUCCESS);
}
