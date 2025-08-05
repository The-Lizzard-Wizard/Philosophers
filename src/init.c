/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/05 14:48:45 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>

void init_philo(t_data *data, t_philo *philo)
{
	(void)data;
	philo->is_sleep = FALSE;
	philo->is_eating = FALSE;
	philo->is_thinking = FALSE;
	philo->nb_philo = data->nb_philo;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->nb_philo;
	philo->time_to_sleep = data->time_to_sleep;
	philo->first_milisec = data->first_milisec;
	philo->fork_left = malloc(sizeof(t_fork));
	pthread_mutex_init(&philo->fork_left->mutex, NULL);
	philo->fork_right = NULL;
	philo->iamdie = FALSE;
}

void init_table(t_data *data)
{
	unsigned int i;

	data->first_milisec = get_time(0);
	data->philo_list = malloc(sizeof(t_philo) * data->nb_philo);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo_list[i].id = i;
		init_philo(data, &data->philo_list[i]);
		pthread_create(&data->philo_list[i].philo_tid, NULL, &philo_routin,
						&data->philo_list[i]);
	}
}