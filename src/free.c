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
		destroy_protect_flag(philo_list[index].fork_left);
		pthread_mutex_destroy(&philo_list[index].eat_count_mutex);
		pthread_mutex_destroy(&philo_list[index].eat_update_mutex);
		index++;
	}
	free(philo_list);
}

int	free_data(t_data *data)
{
	destroy_protect_flag(data->run);
	destroy_protect_flag(data->can_draw);
	free(data);
	return (0);
}

void	destroy_protect_flag(t_protect_flag *fork)
{
	pthread_mutex_destroy(&fork->mutex);
	free(fork);
}

int	double_free(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
	return (0);
}
