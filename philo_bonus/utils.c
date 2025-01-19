/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:02:17 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/19 14:47:07 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
1 second = 1.000 milliseconds
1 millisecond = 1.000 microseconds
*/

uint64_t	current_time(void)
{
	struct timeval	cur_t;
	uint64_t		cur_t_ms;

	gettimeofday(&cur_t, NULL);
	cur_t_ms = 1000 * cur_t.tv_sec + cur_t.tv_usec / 1000;
	return (cur_t_ms);
}

/*
Precision dictated function
to avoid oversleeping with regular usleep().
*/

void	custom_sleep(uint64_t ms)
{
	uint64_t	start;

	start = current_time();
	while (current_time() - start < ms)
		usleep(100);
}

void	free_args(t_args *args)
{
	unsigned int	i;

	// if (args->forks)
	// 	free(args->forks);
	// i = 0;
	// if (args->mtx_forks)
	// {
	// 	while (i < args->num_ph)
	// 	{
	// 		pthread_mutex_destroy(&args->mtx_forks[i]);
	// 		i++;
	// 	}
	// 	free(args->mtx_forks);
	// }
	i = 0;
	if (args->phs)
	{
		while (i < args->num_ph)
		{
			// pthread_mutex_destroy(&args->phs[i].ate_m);
			// pthread_mutex_destroy(&args->phs[i].last_meal_m);
			i++;
		}
		free(args->phs);
	}
}

void	print_state(t_ph *ph, char *msg)
{
	uint64_t	elapsed;

	// pthread_mutex_lock(&ph->args->print_m);
	// pthread_mutex_lock(&ph->args->rip_m);
	if (!ph->args->rip)
	{
		elapsed = current_time() - ph->args->sim_start;
		printf("%llu %i %s\n", elapsed, ph->id, msg);
	}
	// pthread_mutex_unlock(&ph->args->rip_m);
	// pthread_mutex_unlock(&ph->args->print_m);
}
