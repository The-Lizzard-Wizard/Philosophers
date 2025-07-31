/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:09 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/23 15:41:47 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#define TRUE 1
#define FALSE 2

typedef struct	s_fork
{
	pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
	int				id;
	int				is_sleep;
	int				is_eating;
	int				is_thinking;
	pthread_t		philo_tid;
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	t_fork			*fork_left;
	t_fork			*fork_right;
} t_philo;

typedef struct s_table
{
	t_philo	*philo;
} t_table;

typedef struct	s_data
{
	t_table			*table;
	t_philo			*philo_list;
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
} t_data;

int	ft_atoi(const char *nptr);