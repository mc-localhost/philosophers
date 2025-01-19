/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:02:26 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/19 13:04:20 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
There is a process for every philosopher
but the main process is not a philosopher.
*/

int	create_processes(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		if ()
			return (printf("Couldn't fork\n"), free_args(args), 1);
		i++;
	}
	
	return (0);
}

int	wait_for_processes(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		
		i++;
	}

	return (0);
}
