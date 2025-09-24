/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:32:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/19 02:32:54 by gchauvet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_update_mutex);
	if (get_time(philo->first_milisec + philo->last_eat) > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat_update_mutex);
		print_status(philo, "died");
		drop_fork(philo);
		set_mutex_value(philo->run, FALSE);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->eat_update_mutex);
	return (FALSE);
}

void	check_eat(t_data *data, unsigned int i, unsigned int *food_ok)
{
	if (data->nb_philo > 1)
	{
		pthread_mutex_lock(&data->philo_list[i].eat_count_mutex);
		if (data->philo_list[i].eat_count >= data->nb_eat)
			(*food_ok)++;
		pthread_mutex_unlock(&data->philo_list[i].eat_count_mutex);
	}
}

void	*death_routin(void *pdata)
{
	unsigned int	i;
	unsigned int	food_ok;
	t_data			*data;

	data = (t_data *)pdata;
	while (get_time(0) < data->first_milisec)
		usleep(100);
	while (is_true(data->run))
	{
		food_ok = 0;
		i = 0;
		while (i < data->nb_philo)
		{
			is_die(&data->philo_list[i]);
			check_eat(data, i, &food_ok);
			i++;
		}
		if (data->eat_limite == TRUE)
			if (food_ok >= data->nb_philo)
				set_mutex_value(data->run, FALSE);
		usleep(100);
	}
	return (NULL);
}
