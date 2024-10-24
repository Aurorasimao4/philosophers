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

#include "philo.h"

int creating_thread(t_philosopher *philo, t_norms *norms)
{
   int					i;

	i = 0;
	norms->first_timestamp = timestamp();
	while (i < norms->philo_nbr)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])) != 0)
			return (0 * printf("thread nao criada"));
		pthread_mutex_lock(&(norms->meal_check));
		philo[i].t_last_meal = timestamp();
		//pthread_mutex_unlock(&(norms->meal_check));
		i++;
	}

    return 0; // Sucesso
}

int	main(int argc, char **argv)
{
	int			res;
	t_norms		norms;
	t_philosopher *philo;

	if (argc != 5 && argc != 6)
		return (write_error("invalid parameters"));
	if (init_all(philo, &norms, argv) != 0)
		return (write(1, "Erro\n", 5));
	init_philosophers(&philo, &norms);
	if (creating_thread(philo, &norms) != 0)
		printf("Algo ocorreu mal\n");
	
}
