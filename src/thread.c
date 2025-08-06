/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:02 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/06 16:25:02 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	thread_wait(long int milisec)
{
	long int	end_sleep;

	end_sleep = get_time(0) + milisec;
	while (get_time(0) < end_sleep)
		usleep(50);
}

// void	philo_sleep(t_philo *philo)
// {
// 	thread_wait(philo->time_to_sleep);
// }

int		is_die(t_philo *philo)
{
	if (get_time(philo->first_milisec + philo->last_eat) > philo->time_to_die)
		return (TRUE);
	return (FALSE);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left->mutex);
	philo->fork_left->flag = TRUE;
	printf("%ld %d has taken a fork\n", get_time(philo->first_milisec), philo->id);
	pthread_mutex_lock(&philo->fork_right->mutex);
	philo->fork_right->flag = TRUE;
	printf("%ld %d has taken a fork\n", get_time(philo->first_milisec), philo->id);
	printf("%ld %d is eating\n", get_time(philo->first_milisec), philo->id);
	philo->last_eat = get_time(philo->first_milisec);
	thread_wait(philo->time_to_eat);
	if (is_die(philo) == TRUE)
	{
		philo->fork_left->flag = FALSE;
		pthread_mutex_unlock(&philo->fork_left->mutex);
		philo->fork_right->flag = FALSE;
		pthread_mutex_unlock(&philo->fork_right->mutex);
		return ;
	}
	printf("%ld %d is sleeping\n", get_time(philo->first_milisec), philo->id);
	philo->fork_left->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_left->mutex);
	philo->fork_right->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_right->mutex);
	thread_wait(philo->time_to_sleep);
}

// void	philo_think(t_philo *philo)
// {
	
// }

void	philo_eat_think_sleep(t_philo *philo)
{
	philo_eat(philo);
}

void	*philo_routin(void *data)
{
	pthread_t self_tid;
	t_philo *philo;

	philo = (t_philo *)data;

	self_tid = pthread_self();
	//printf("id : %i tid :  %ld\n", philo->id, self_tid);
	thread_wait(START_DEL);
	if (philo->id % 2 == 1)
		thread_wait(START_DEL);
	while (is_die(philo) == FALSE)
	{
		printf("%ld %d is thinking\n", get_time(philo->first_milisec), philo->id);
		philo_eat_think_sleep(philo);
	}
	printf("%ld %d died\n", get_time(philo->first_milisec), philo->id);
	return (NULL);
}
