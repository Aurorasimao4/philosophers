/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimao <asimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:16:29 by asimao            #+#    #+#             */
/*   Updated: 2024/10/23 05:55:59 by asimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "philo.h"

int	creating_thread(t_norms *norms)
{
	t_philosopher *philo;
	int i;

	i = 0;
	philo = norms->philosophers;
	norms->first_timestamp = timestamp();
	while (i < norms->num_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])))
			return (1);
        pthread_mutex_lock(&(norms->meal_check));
        philo[i].t_last_meal = timestamp();
        pthread_mutex_unlock(&(norms->meal_check));
        i++;
	}
}

int main(int ac, char **av)
{
    t_norms norms;
    int res;

    if(ac != 5 && ac != 6)
        return(write_error("invalid parameters"));
    res = init_all(&norms. av);
    if(res == init_all(&norms, av));
        return(write(1, ""))
}
