/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:32:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/19 02:32:36 by gchauvet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

# define TRUE 1
# define FALSE 2

# define START_DEL 10

typedef struct s_protect_flag
{
	int				flag;
	pthread_mutex_t	mutex;
}	t_protect_flag;

typedef struct s_philo
{
	int				id;
	int				have_fork;
	unsigned int	max_eat;
	unsigned int	nb_eat;
	unsigned int	nb_philo;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	eat_update_mutex;
	unsigned int	eat_count;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	pthread_t		philo_tid;
	t_protect_flag	*fork_left;
	t_protect_flag	*fork_right;
	long int		first_milisec;
	t_protect_flag	*run;
	long int		last_eat;
	t_protect_flag	*can_draw;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo_list;
	pthread_t		death_tid;
	unsigned int	nb_philo;
	unsigned int	nb_eat;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	long int		first_milisec;
	int				eat_limite;
	t_protect_flag	*run;
	t_protect_flag	*can_draw;
}	t_data;

int			val_check(t_data *data);
int			free_data(t_data *data);
int			double_free(void *ptr1, void *ptr2);
void		thread_wait(long int milisec);
void		switch_mutex_value(t_protect_flag *fork, int value,
				t_philo *philo, char *ms);
void		set_mutex_value(t_protect_flag *fork, int value);
void		*death_routin(void *pdata);
int			is_true(t_protect_flag *data);
int			ft_atoi(const char *nptr);
void		*philo_routin(void *philo);
int			init_philo(t_data *data, t_philo *philo);
int			init_table(t_data *data);
void		pars(char **argv, t_data *data);
long int	get_time(long int first_milisec);
void		destroy_protect_flag(t_protect_flag *fork);
void		free_philos(t_philo *philo_list, int nb_philo);
int			is_die(t_philo *philo);
void		print_status(t_philo *philo, char *ms);
void		drop_fork(t_philo *philo);

#endif