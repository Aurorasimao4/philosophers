/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimao <asimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 04:59:03 by asimao            #+#    #+#             */
/*   Updated: 2024/10/23 05:18:27 by asimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct	s_norms;

typedef struct s_norms
{
	int				philo_nbr;
	int				time_to_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				died;
	int				all_ate;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	m_died;
	pthread_mutex_t	m_eat_all;
	pthread_mutex_t	m_waiting;
	pthread_mutex_t	m_all_ate;
	//t_philosopher	philosophers[250];
}					t_norms;

typedef struct s_philosopher
{
	int					num_ate;
	int					id;
	int					l_fork_id;
	int					r_fork_id;
	t_norms				*norms;
	pthread_t			thread_id;
	long long			t_last_meal;
}			t_philosopher;

int	init_philosophers(t_philosopher **p, t_norms *norms);
int					write_error(char *str);
int					error_manager(int error);
int					init_all(t_philosopher *p, t_norms *norms, char **argv);
int					ft_atoi(const char *str);
void				action_write(t_norms *norms, int id, char *string);
size_t				timestamp(void);
long long			time_diff(long long past, long long pres);
void				waiting(long long time, t_norms *norms);
void				exit_program(t_norms *norms, t_philosopher *philos);
int creating_thread(t_philosopher *philo, t_norms *norms);
void				*p_thread(void *my_philo);
void				death_verify(t_norms *n, t_philosopher *p);

#endif
