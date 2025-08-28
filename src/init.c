/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/28 13:47:12 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>

int	init_philo_fork(t_data *data, t_philo *philo)
{
	int	nightbor_id;

	nightbor_id = ((philo->id - 1) + data->nb_philo - 1) % data->nb_philo;
	philo->fork_left = malloc(sizeof(t_fork));
	if (!philo->fork_left)
		return (0);
	if (pthread_mutex_init(&philo->fork_left->mutex, NULL) != 0)
	{
		free(philo->fork_left);
		return (0);
	}
	philo->fork_left->flag = FALSE;
	if (philo->id > 1)
		philo->fork_right = data->philo_list[nightbor_id].fork_left;
	if (philo->id == (int)philo->nb_philo)
		data->philo_list[0].fork_right = philo->fork_left;
	return (1);
}

int	init_philo(t_data *data, t_philo *philo)
{
	philo->max_eat = data->nb_eat;
	philo->nb_eat = 0;
	philo->have_fork = 0;
	philo->nb_philo = data->nb_philo;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->first_milisec = data->first_milisec;
	philo->can_draw = data->can_draw;
	philo->fork_right = NULL;
	philo->last_eat = 0;
	philo->thefork = data->someonedie;
	if (init_philo_fork(data, philo) == 0)
		return (0);
	return (1);
}

int	init_table_2(t_data *data)
{
	data->first_milisec = get_time(0) + START_DEL;
	data->philo_list = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo_list)
		return (0);
	data->someonedie = malloc(sizeof(t_fork));
	if (!data->someonedie)
		return (free(data->philo_list), 0);
	data->can_draw = malloc(sizeof(t_fork));
	if (!data->can_draw)
		return (free(data->philo_list), free(data->someonedie), 0);
	if (pthread_mutex_init(&data->someonedie->mutex, NULL) != 0)
		return (free(data->someonedie), free(data->philo_list), 0);
	if (pthread_mutex_init(&data->can_draw->mutex, NULL) != 0)
		return (free(data->can_draw),
			free(data->someonedie), free(data->philo_list), 0);
	data->someonedie->flag = FALSE;
	data->can_draw->flag = FALSE;
	return (1);
}

int	init_table(t_data *data)
{
	unsigned int	i;

	if (init_table_2(data) == 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo_list[i].id = i + 1;
		if (init_philo(data, &data->philo_list[i]) == 0)
		{
			destroy_fork(data->someonedie);
			free_philos(data->philo_list, i);
			return (0);
		}
		if (pthread_create(&data->philo_list[i].philo_tid,
				NULL, &philo_routin, &data->philo_list[i]) != 0)
		{
			destroy_fork(data->someonedie);
			free_philos(data->philo_list, i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}
