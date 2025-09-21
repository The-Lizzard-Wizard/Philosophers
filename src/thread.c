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

void	thread_wait(long int milisec)
{
	long int	end_sleep;

	end_sleep = get_time(0) + milisec;
	while (get_time(0) < end_sleep)
	{
		usleep(500);
	}
}

void	take_fork(t_philo *philo)
{
	while (1)
	{
		if (!is_true(philo->fork_left))
		{
			set_mutex_value(philo->fork_left, TRUE);
			print_status(philo, "has taken a fork");
			philo->have_fork++;
		}
		if (!is_true(philo->fork_right))
		{
			set_mutex_value(philo->fork_right, TRUE);
			print_status(philo, "has taken a fork");
			philo->have_fork++;
		}
		if (philo->have_fork == 2)
			break ;
		usleep(100);
	}
}

void	drop_fork(t_philo *philo)
{
	while (1)
	{
		if (is_true(philo->fork_left))
		{
			set_mutex_value(philo->fork_left, FALSE);
			philo->have_fork--;
		}
		if (!is_true(philo->fork_right))
		{
			set_mutex_value(philo->fork_right, FALSE);
			philo->have_fork--;
		}
		if (philo->have_fork == 0)
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	take_fork(philo);
	print_status(philo, "is eating");
	philo->nb_eat++;
	philo->last_eat = get_time(philo->first_milisec);
	thread_wait(philo->time_to_eat);
	print_status(philo, "is sleeping");
	drop_fork(philo);
	thread_wait(philo->time_to_sleep);
}

void	*philo_routin(void *data)
{
	t_philo		*philo;
	int			start;

	start = 0;
	philo = (t_philo *)data;
	while (get_time(0) < philo->first_milisec)
		usleep(100);
	while (is_true(philo->run))
	{
		print_status(philo, "is thinking");
		if (start == 0)
		{
			if (philo->id % 2 == 1)
				thread_wait(10);
			start = 1;
		}
		philo_eat(philo);
		usleep(100);
	}
	return (NULL);
}
