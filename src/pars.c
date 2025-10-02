/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:45:15 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/18 14:59:55 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>

int	val_check(t_data *data)
{
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (data->eat_limite == TRUE && data->nb_eat == 0))
	{
		printf("arg error : try a higher value\n");
		return (0);
	}
	return (1);
}

void	pars(char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->eat_limite = TRUE;
		data->nb_eat = ft_atoi(argv[5]);
	}
	else
	{
		data->nb_eat = 0;
		data->eat_limite = FALSE;
	}
}
