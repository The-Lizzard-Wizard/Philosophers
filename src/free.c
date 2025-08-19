/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:37:33 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/18 16:25:41 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdlib.h>

void	free_philos(t_philo *philo_list, int nb_philo)
{
	int	index;

	index = 0;
	while (index <= nb_philo - 1)
	{
		destroy_fork(philo_list[index].fork_left);
		index++;
	}
	free(philo_list);
}

void	destroy_fork(t_fork *fork)
{
	pthread_mutex_destroy(&fork->mutex);
	free(fork);
}
