/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menaged_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimao <asimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 05:57:42 by asimao            #+#    #+#             */
/*   Updated: 2024/10/23 05:57:48 by asimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("VERIFIQUE OS ARGUMENTOS"));
	if (error == 2)
		return (write_error("ERRO AO INICIALIZAR A MUTEX"));
	return (1);
}
