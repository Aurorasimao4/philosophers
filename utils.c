/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimao <asimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:56:59 by asimao            #+#    #+#             */
/*   Updated: 2024/10/23 05:57:14 by asimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

size_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	waiting(long long time, t_norms *norms)
{
	long long	now;

	now = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(norms->m_died));
		if (norms->died)
		{
			pthread_mutex_unlock(&(norms->m_died));
			return ;
		}
		pthread_mutex_unlock(&(norms->m_died));
		if (time_diff(now, timestamp()) >= time)
			break ;
	}
}

void	action_write(t_norms *norms, int id, char *string)
{
	pthread_mutex_lock(&(norms->writing));
	pthread_mutex_lock(&(norms->m_died));
	if (!(norms->died))
	{
		printf("%lld ", timestamp() - norms->first_timestamp);
		printf("%d ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(norms->m_died));
	pthread_mutex_unlock(&(norms->writing));
	return ;
}
