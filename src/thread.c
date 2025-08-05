/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:46:02 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/05 14:49:57 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	philo_sleep(t_philo *philo, long int sleeptime)
{

}

void	philo_eat(t_philo *philo)
{

}

void	philo_think(t_philo *philo)
{
	
}

void	philo_eat_think_sleep(t_philo *philo)
{
	
}

void	*philo_routin(void *data)
{
	pthread_t self_tid;
	t_philo *philo;

	philo = (t_philo *)data;

	self_tid = pthread_self();
	printf("id : %i tid :  %ld\n", philo->id, self_tid);
	while (philo->iamdie == FALSE)
	{
		printf("id : %d milisec : %ld\n", philo->id, get_time(philo->first_milisec));
		if (philo->id % 2 == 1)
		{
			if (get_time(philo->first_milisec) > 250)
			{
				philo_eat_think_sleep(philo);
			}
		}
		else
		{
			philo_eat_think_sleep(philo);
		}
	}
	return (NULL);
}
