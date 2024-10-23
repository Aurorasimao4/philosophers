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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct s_norms;

typedef struct s_philosopher
{
    int num_ate;
    int id;
    int l_fork_id;
    int r_fork_id;
    long long   t_last_meal;
    struct s_norms *norms;
    pthread_t thread_id;
                t_philosopher;   
}

typedef struct s_norms
{
    int time_to_death;
    int time_to_eat;
    int time_to_sleep;
    int  eat_nbr;
    int philo_nbr;
    int died;
    long long   first_timstamp;
    pthread_mutex_t	meal_verify;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	m_died;
	pthread_mutex_t	m_eat_all;
	pthread_mutex_t	m_waiting;
	pthread_mutex_t	m_all_ate;
	t_philosopher	philosophers[250];
}					t_norms;
}






#endif
