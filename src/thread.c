/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:02 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/18 11:26:48 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_status(t_philo *philo, char *ms)
{
	printf("%ld %d %s\n", get_time(philo->first_milisec), philo->id, ms);
}

int	is_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->thefork->mutex);
	if (philo->thefork->flag == TRUE)
	{
		pthread_mutex_unlock(&philo->thefork->mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->thefork->mutex);
	if (get_time(philo->first_milisec + philo->last_eat) > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->thefork->mutex);
		philo->thefork->flag = TRUE;
		pthread_mutex_unlock(&philo->thefork->mutex);
		print_status(philo, "died");
		return (TRUE);
	}
	return (FALSE);
}

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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left->mutex);
	philo->fork_left->flag = TRUE;
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_right->mutex);
	philo->fork_right->flag = TRUE;
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_eat = get_time(philo->first_milisec);
	thread_wait(philo->time_to_eat, philo);
	if (is_die(philo) == TRUE)
	{
		philo->fork_left->flag = FALSE;
		pthread_mutex_unlock(&philo->fork_left->mutex);
		philo->fork_right->flag = FALSE;
		pthread_mutex_unlock(&philo->fork_right->mutex);
		return ;
	}
	print_status(philo, "is sleeping");
	philo->fork_left->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_left->mutex);
	philo->fork_right->flag = FALSE;
	pthread_mutex_unlock(&philo->fork_right->mutex);
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
