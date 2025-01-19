/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:48:49 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/07 16:19:29 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
There is a thread for every philosopher
and one additional thread to monitor them.
*/

int	create_threads(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		if (pthread_create(&args->phs[i].th, NULL, &life, &args->phs[i]) != 0)
			return (printf("Couldn't create thread\n"), free_args(args), 1);
		i++;
	}
	if (pthread_create(&args->waiter_th, NULL, &waiter, args) != 0)
		return (printf("Couldn't create waiter thread\n"), free_args(args), 1);
	return (0);
}

int	join_threads(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		if (pthread_join(args->phs[i].th, NULL) != 0)
			return (printf("Couldn't join thread\n"), free_args(args), 1);
		i++;
	}
	if (pthread_join(args->waiter_th, NULL) != 0)
		return (printf("Couldn't join waiter thread\n"), free_args(args), 1);
	return (0);
}
