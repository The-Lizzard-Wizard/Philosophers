/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:27:29 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/25 14:06:28 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	thread_wait(long int milisec)
{
	long int	end_sleep;

	end_sleep = get_time(0) + milisec;
	while (get_time(0) < end_sleep)
	{
		usleep(500);
	}
}

void	set_mutex_value(t_fork *fork, int value)
{
	pthread_mutex_lock(&fork->mutex);
	fork->flag = value;
	pthread_mutex_unlock(&fork->mutex);
}

int	is_true(t_fork *data)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&data->mutex);
	if (data->flag == TRUE)
		flag = 1;
	pthread_mutex_unlock(&data->mutex);
	return (flag);
}

void	print_status(t_philo *philo, char *ms)
{
	pthread_mutex_lock(&philo->can_draw->mutex);
	pthread_mutex_lock(&philo->run->mutex);
	if (philo->run->flag == FALSE)
	{
		pthread_mutex_unlock(&philo->run->mutex);
		pthread_mutex_unlock(&philo->can_draw->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->run->mutex);
	pthread_mutex_lock(&philo->eat_update_mutex);
	printf("%ld %d %s\n", get_time(philo->first_milisec), philo->id, ms);
	pthread_mutex_unlock(&philo->eat_update_mutex);
	pthread_mutex_unlock(&philo->can_draw->mutex);
}
