/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:02 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/28 13:54:31 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	take_drop(t_fork *fork, t_philo *philo, int flag)
{
	if (flag == 1)
	{
		if (fork->flag == FALSE)
		{
			fork->flag = TRUE;
			print_status(philo, "has taken a fork");
			philo->have_fork++;
		}
	}
	else if (flag == 2)
	{
		if (fork->flag == TRUE)
		{
			fork->flag = FALSE;
			philo->have_fork--;
		}
	}
}

void	take_fork(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->fork_left->mutex);
			take_drop(philo->fork_left, philo, 1);
			pthread_mutex_unlock(&philo->fork_left->mutex);
			pthread_mutex_lock(&philo->fork_right->mutex);
			take_drop(philo->fork_right, philo, 1);
			pthread_mutex_unlock(&philo->fork_right->mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->fork_right->mutex);
			take_drop(philo->fork_right, philo, 1);
			pthread_mutex_unlock(&philo->fork_right->mutex);
			pthread_mutex_lock(&philo->fork_left->mutex);
			take_drop(philo->fork_left, philo, 1);
			pthread_mutex_unlock(&philo->fork_left->mutex);
		}
		if (philo->have_fork == 2)
			break ;
		usleep(100);
	}
}

void	drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_left->mutex);
		take_drop(philo->fork_left, philo, 2);
		pthread_mutex_unlock(&philo->fork_left->mutex);
		pthread_mutex_lock(&philo->fork_right->mutex);
		take_drop(philo->fork_right, philo, 2);
		pthread_mutex_unlock(&philo->fork_right->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_right->mutex);
		take_drop(philo->fork_right, philo, 2);
		pthread_mutex_unlock(&philo->fork_right->mutex);
		pthread_mutex_lock(&philo->fork_left->mutex);
		take_drop(philo->fork_left, philo, 2);
		pthread_mutex_unlock(&philo->fork_left->mutex);
	}
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	philo->last_eat = get_time(philo->first_milisec);
	thread_wait(philo->time_to_eat);
	drop_fork(philo);
	print_status(philo, "is sleeping");
	thread_wait(philo->time_to_sleep);
}

void	*philo_routin(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (get_time(0) < philo->first_milisec)
		usleep(100);
	print_status(philo, "is thinking");
	if (philo->id % 2 == 1)
		thread_wait(10);
	while (is_true(philo->run))
	{
		philo_eat(philo);
		print_status(philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}
