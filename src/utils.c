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

int	is_die(t_philo *philo)
{
	if (philo->nb_eat >= philo->max_eat)
		return (TRUE);
	pthread_mutex_lock(&philo->thefork->mutex);
	if (philo->thefork->flag == TRUE)
	{
		pthread_mutex_unlock(&philo->thefork->mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->thefork->mutex);
	if (get_time(philo->first_milisec + philo->last_eat) > philo->time_to_die)
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->thefork->mutex);
		philo->thefork->flag = TRUE;
		pthread_mutex_unlock(&philo->thefork->mutex);
		return (TRUE);
	}
	return (FALSE);
}

void	print_status(t_philo *philo, char *ms)
{
	pthread_mutex_lock(&philo->can_draw->mutex);
	pthread_mutex_lock(&philo->thefork->mutex);
	if (philo->thefork->flag == TRUE)
	{
		pthread_mutex_unlock(&philo->thefork->mutex);
		pthread_mutex_unlock(&philo->can_draw->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->thefork->mutex);
	printf("%ld %d %s\n", get_time(philo->first_milisec), philo->id, ms);
	pthread_mutex_unlock(&philo->can_draw->mutex);
}

static int	calculate_number(const char *nptr, int n, int i)
{
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	n;
	int	s2;

	i = 0;
	n = 0;
	s = 1;
	s2 = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * -1;
		i++;
		s2++;
	}
	if (s2 >= 2)
		return (0);
	n = calculate_number(nptr, n, i);
	return (n * s);
}
