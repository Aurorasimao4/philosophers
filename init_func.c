/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:58:26 by asimao            #+#    #+#             */
/*   Updated: 2024/10/24 20:44:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_norms *norms)
{
	/*int	i;

	i = norms->philo_nbr + 1;
	while (--i > 0)
	{
		if (pthread_mutex_init(&(norms->forks[i]), NULL))
			return (1);
	}*/
	if (pthread_mutex_init(&(norms->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(norms->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(norms->m_died), NULL))
		return (1);
	if (pthread_mutex_init(&(norms->m_eat_all), NULL))
		return (1);
	if (pthread_mutex_init(&(norms->m_waiting), NULL))
		return (1);
	if (pthread_mutex_init(&(norms->m_all_ate), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_philosopher **p, t_norms *norms) {
    int i;
    int	right;

    *p = (t_philosopher *)malloc(sizeof(t_philosopher) * norms->philo_nbr);
    norms->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * norms->philo_nbr);
    if (!*p || !norms->forks) {
        printf("Erro ao alocar philo ou garfos\n");
        return -1; // Retorne um código de erro apropriado
    }
    
    for (i = 0; i < norms->philo_nbr; i++) {
        (*p)[i].id = i + 1;
        (*p)[i].num_ate = 0;
        (*p)[i].norms = norms;
	if ((*p)[i].id == 1)
		right = norms->philo_nbr;
	else
		right = (*p)[i].id - 1;
	(*p)[i].l_fork_id = i + 1;
	(*p)[i].r_fork_id = right;
	(*p)[i].t_last_meal = 0;
    }

    for (i = 0; i < norms->philo_nbr; i++) {
        pthread_mutex_init(&(norms->forks[i]), NULL);
    }
    return 0; // Sucesso
    }

/*int	init_philosophers(t_philosopher *p, t_norms *norms)
{
	int	i;
	int	right;

	p =(t_philosopher *) malloc(sizeof(t_philosopher ) * norms->philo_nbr);
	norms->forks = malloc(sizeof(pthread_mutex_t) * norms->philo_nbr);
	if(!p || !norms->forks)
		return (0 * printf("Erro ao alocar philo ou garfos\n"));
	i = 0;
	while (i < norms->philo_nbr)
	{
		p[i].id = i + 1;
		p[i].num_ate = 0;
		p[i].norms = norms;
		pthread_mutex_init(&(norms->forks[i]), NULL);
		i++;
	}
	printf("Passou aqui 3\n");
	return (0);
}*/

int	init_all(t_philosopher *philo, t_norms *norms, char **argv)
{
	norms->philo_nbr = ft_atoi(argv[1]);
	norms->time_to_death = ft_atoi(argv[2]);
	norms->time_to_eat = ft_atoi(argv[3]);
	norms->time_to_sleep = ft_atoi(argv[4]);
	norms->all_ate = 0;
	norms->died = 0;
	if (norms->philo_nbr == 1)
		return (3);
	if (norms->philo_nbr < 2 || norms->time_to_death < 60 \
	|| norms->time_to_eat < 60 || norms->time_to_sleep < 60 \
	|| norms->philo_nbr > 200)
		return (1);
	if (argv[5])
	{
		norms->nb_eat = ft_atoi(argv[5]);
		if (norms->nb_eat <= 0)
			return (1);
	}
	else
		norms->nb_eat = -1;
	if (init_mutex(norms))
		return (2);
	return (0);
}

void	exit_program(t_norms *norms, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < norms->philo_nbr)
		pthread_join(philos[i].thread_id, NULL);
	i = 0;
	while (++i <= norms->philo_nbr)
		pthread_mutex_destroy(&(norms->forks[i]));
	pthread_mutex_destroy(&(norms->writing));
	pthread_mutex_destroy(&(norms->m_died));
	pthread_mutex_destroy(&(norms->m_eat_all));
	pthread_mutex_destroy(&(norms->m_waiting));
	pthread_mutex_destroy(&(norms->m_all_ate));
}
