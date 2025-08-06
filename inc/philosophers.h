/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:09 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/06 15:44:12 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 2

typedef struct	s_fork
{
	int				flag;
	pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
	int				id;
	int				is_sleep;
	int				is_eating;
	int				is_thinking;
	unsigned int	nb_philo;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	pthread_t		philo_tid;
	t_fork			*fork_left;
	t_fork			*fork_right;
	long int		first_milisec;
	int				iamdie;
	long int		last_eat;
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
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	long int		first_milisec;
	t_fork			*someoneide;
} t_data;

int		ft_atoi(const char *nptr);
void	*philo_routin(void *philo);
void	init_philo(t_data *data, t_philo *philo);
void	init_table(t_data *data);
void	pars(char **argv, t_data *data);
long int	get_time(long int first_milisec);