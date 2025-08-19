/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:02 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/19 13:56:57 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	thread_wait(long int milisec, t_philo *philo)
{
	long int	end_sleep;

	end_sleep = get_time(0) + milisec;
	while (get_time(0) < end_sleep)
	{
		usleep(50);
		if (is_die(philo) == TRUE)
			break ;
	}
}

void	take_fork(t_philo *philo)
{
	while (philo->have_fork < 2 && is_die(philo) == FALSE)
	{
		pthread_mutex_lock(&philo->fork_left->mutex);
		if (philo->fork_left->flag == FALSE)
		{
			print_status(philo, "has taken a fork");
			philo->fork_left->flag = TRUE;
			philo->have_fork++;
		}
		pthread_mutex_unlock(&philo->fork_left->mutex);
		pthread_mutex_lock(&philo->fork_right->mutex);
		if (philo->fork_right->flag == FALSE)
		{
			print_status(philo, "has taken a fork");
			philo->fork_right->flag = TRUE;
			philo->have_fork++;
		}
		pthread_mutex_unlock(&philo->fork_right->mutex);
	}
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left->mutex);
	philo->fork_left->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_left->mutex);
	pthread_mutex_lock(&philo->fork_right->mutex);
	philo->fork_right->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_right->mutex);
	philo->have_fork = 0;
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo);
	if (is_die(philo) == TRUE)
	{
		drop_fork(philo);
		return ;
	}
	print_status(philo, "is eating");
	philo->nb_eat++;
	philo->last_eat = get_time(philo->first_milisec);
	thread_wait(philo->time_to_eat, philo);
	if (is_die(philo) == TRUE)
	{
		drop_fork(philo);
		return ;
	}
	print_status(philo, "is sleeping");
	drop_fork(philo);
	thread_wait(philo->time_to_sleep, philo);
}

void	*philo_routin(void *data)
{
	pthread_t	self_tid;
	t_philo		*philo;

	philo = (t_philo *)data;
	self_tid = pthread_self();
	thread_wait(START_DEL, philo);
	if (philo->id % 2 == 1)
		thread_wait(START_DEL, philo);
	while (is_die(philo) == FALSE)
	{
		print_status(philo, "is thinking");
		philo_eat(philo);
	}
	return (NULL);
}
