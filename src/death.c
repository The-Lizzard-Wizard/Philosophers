/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:32:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/19 02:32:54 by gchauvet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	is_die(t_philo *philo)
{
	if (get_time(philo->first_milisec + philo->last_eat) > philo->time_to_die)
	{
		print_status(philo, "died");
		set_mutex_value(philo->run, TRUE)
		return (TRUE);
	}
	return (FALSE);
}

void	*death_routin(t_data *data)
{
	unsigned int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		
		i++;
	}
}