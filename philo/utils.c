/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:03:10 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/03 16:55:04 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
1 second = 1.000 milliseconds
1 millisecond = 1.000 microseconds
*/

unsigned long long	current_time(void)
{
	struct timeval	cur_t;

	gettimeofday(&cur_t, NULL);
	return (1000 * cur_t.tv_sec + cur_t.tv_usec / 1000);
}

/*
Precision dictated function
to avoid oversleeping with regular	usleep(void).
*/

void	custom_sleep(unsigned long long ms)
{
	unsigned long long	start;

	start = current_time();
	while (current_time() - start < ms)
		usleep(100);
}

/*
Mutex can be destroyed only if it was unlocked (supposedly),
so we should unlock locked forks, when someone is still eating
at the moment when simulation should end.
*/

static void	unlock_locked(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		if (args->forks[i] == true)
			pthread_mutex_unlock(&args->mtx_forks[i]);
		i++;
	}
	free(args->forks);
}

void	free_args(t_args *args)
{
	unsigned int	i;

	if (args->forks)
		unlock_locked(args);
	i = 0;
	if (args->mtx_forks)
	{
		while (i < args->num_ph)
			pthread_mutex_destroy(&args->mtx_forks[i++]);
		free(args->mtx_forks);
	}
	i = 0;
	if (args->phs)
	{
		while (i < args->num_ph)
		{
			pthread_mutex_destroy(&args->phs[i].ate_m);
			pthread_mutex_destroy(&args->phs[i].last_meal_m);
			i++;
		}
		free(args->phs);
	}
	pthread_mutex_unlock(&args->print_m);
	pthread_mutex_destroy(&args->print_m);
	pthread_mutex_destroy(&args->rip_m);
}

void	print_state(t_ph *ph, char *msg)
{
	pthread_mutex_lock(&ph->args->rip_m);
	if (!ph->args->rip)
	{
		pthread_mutex_lock(&ph->args->print_m);
		printf("%llu %u %s\n", current_time() - ph->args->sim_start, ph->id,
			msg);
		pthread_mutex_unlock(&ph->args->print_m);
	}
	pthread_mutex_unlock(&ph->args->rip_m);
}
