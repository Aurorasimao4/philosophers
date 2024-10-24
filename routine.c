/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:01:07 by asimao            #+#    #+#             */
/*   Updated: 2024/10/24 21:27:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philosopher *p, t_norms *n, int f_l, int f_r)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&(n->forks[f_l]));
		pthread_mutex_lock(&(n->forks[f_r]));
	}
	else
	{
		pthread_mutex_unlock(&(n->forks[f_r]));
		pthread_mutex_unlock(&(n->forks[f_l]));
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_norms	*norms;

	norms = philo->norms;
	pthread_mutex_lock(&(norms->m_died));
	if (!(norms->died))
	{
		pthread_mutex_unlock(&(norms->m_died));
		lock_forks(philo, norms, philo->l_fork_id, philo->r_fork_id);
		action_write(norms, philo->id, "Pegou o garfo");
		action_write(norms, philo->id, "Pegou o garfo");
		//pthread_mutex_lock(&(norms->meal_check));
		philo->t_last_meal = timestamp();
		//pthread_mutex_unlock(&(norms->meal_check));
		action_write(norms, philo->id, "Esta comendo");
		waiting(norms->time_to_eat, norms);
		pthread_mutex_lock(&(norms->m_all_ate));
		(philo->num_ate)++;
		pthread_mutex_unlock(&(norms->m_all_ate));
		pthread_mutex_unlock(&(norms->forks[philo->l_fork_id]));
		pthread_mutex_unlock(&(norms->forks[philo->r_fork_id]));
	
	}
	else
		pthread_mutex_unlock(&(norms->m_died));
}

void	*p_thread(void *my_philo)
{
	t_philosopher	*philo;
	t_norms			*norms;

	philo = (t_philosopher *)my_philo;
	norms = philo->norms;
	while (1)
	{
		pthread_mutex_lock(&(norms->m_died));
		if (norms->died)
		{
			pthread_mutex_unlock(&(norms->m_died));
			return (NULL);
		}
		pthread_mutex_unlock(&(norms->m_died));
		if (norms->all_ate)
			break ;
		philo_eats(philo);
		if (norms->all_ate)
			break ;
		action_write(norms, philo->id, "Esta dormindo");
		waiting(norms->time_to_sleep, norms);
		action_write(norms, philo->id, "Esta pensando");
	}
	return (NULL);
}

static void	death_verify_aux(t_norms *n, t_philosopher *p, int i)
{
	pthread_mutex_lock(&(n->meal_check));
	if (time_diff(p[i].t_last_meal, timestamp()) > n->time_to_death)
	{
		action_write(n, i + 1, "morto");
		pthread_mutex_lock(&(n->m_died));
		n->died = 1;
		pthread_mutex_unlock(&(n->m_died));
	}
	pthread_mutex_unlock(&(n->meal_check));
}

void	death_verify(t_norms *n, t_philosopher *p)
{
	int	i;

	pthread_mutex_lock(&(n->m_eat_all));
	while (!(n->all_ate))
	{
		i = -1;
		while (++i < n->philo_nbr && !(n->died))
			death_verify_aux(n, p, i);
		pthread_mutex_lock(&(n->m_died));
		if (n->died)
		{
			pthread_mutex_unlock(&(n->m_died));
			break ;
		}
		else
			pthread_mutex_unlock(&(n->m_died));
		i = 0;
		while (n->nb_eat != -1 && i < n->philo_nbr && p[i].num_ate >= n->nb_eat)
			i++;
		if (i == n->philo_nbr)
			n->all_ate = 1;
	}
	pthread_mutex_unlock(&(n->m_eat_all));
}