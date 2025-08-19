/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:42:09 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/19 13:57:56 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

# define TRUE 1
# define FALSE 2

# define START_DEL 10

typedef struct s_fork
{
	int				flag;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				have_fork;
	unsigned int	max_eat;
	unsigned int	nb_eat;
	unsigned int	nb_philo;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	pthread_t		philo_tid;
	t_fork			*fork_left;
	t_fork			*fork_right;
	long int		first_milisec;
	t_fork			*thefork;
	long int		last_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo_list;
	unsigned int	nb_philo;
	unsigned int	nb_eat;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	long int		first_milisec;
	t_fork			*someoneide;
}	t_data;

int			ft_atoi(const char *nptr);
void		*philo_routin(void *philo);
int			init_philo(t_data *data, t_philo *philo);
int			init_table(t_data *data);
void		pars(char **argv, t_data *data);
long int	get_time(long int first_milisec);
void		destroy_fork(t_fork *fork);
void		free_philos(t_philo *philo_list, int nb_philo);
int			is_die(t_philo *philo);
void		print_status(t_philo *philo, char *ms);

#endif