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

void	switch_mutex_value(t_fork *fork, int value, t_philo *philo, char *ms)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->flag != value)
	{
		print_status(philo, ms);
		fork->flag = value;
	}
	pthread_mutex_unlock(&fork->mutex);
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
	if (!is_true(philo->run))
	{
		pthread_mutex_unlock(&philo->can_draw->mutex);
		return ;
	}
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
