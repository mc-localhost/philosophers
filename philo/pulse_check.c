/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:03:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/20 16:31:38 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Simulation must stop if every philosopher has eaten must_eat number of times
(when specified by user input — hence args->must_eat > 0 check).
*/

bool	full_death(t_args *args)
{
	unsigned int	i;
	bool			res;

	i = 0;
	res = true;
	while (args->must_eat > 0 && i < args->num_ph)
	{
		pthread_mutex_lock(&args->phs[i].ate_m);
		res = res && (args->phs[i].ate >= args->must_eat);
		pthread_mutex_unlock(&args->phs[i].ate_m);
		i++;
	}
	if (args->must_eat > 0 && res == true)
	{
		pthread_mutex_lock(&args->rip_m);
		args->rip = true;
		pthread_mutex_lock(&args->print_m);
		write(1, "ALL ATE ENOUGH\n", 15);
		pthread_mutex_unlock(&args->print_m);
		pthread_mutex_unlock(&args->rip_m);
		return (true);
	}
	return (false);
}

/*
Philosopher dies if the start of the last meal
was more than tt_die milliseconds ago.
*/

bool	starvation_death(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->num_ph)
	{
		pthread_mutex_lock(&args->phs[i].last_meal_m);
		if (current_time() - args->phs[i].last_meal > args->tt_die)
		{
			pthread_mutex_lock(&args->rip_m);
			args->rip = true;
			pthread_mutex_lock(&args->print_m);
			printf("%llu %u %s\n", current_time() - args->sim_start,
				args->phs[i].id, "died");
			pthread_mutex_unlock(&args->print_m);
			pthread_mutex_unlock(&args->rip_m);
			pthread_mutex_unlock(&args->phs[i].last_meal_m);
			return (true);
		}
		pthread_mutex_unlock(&args->phs[i].last_meal_m);
		i++;
	}
	return (false);
}

/*
Used by philosophers' routine
in order to get out of the while (1) loop.
*/

bool	someone_rip(t_args *args)
{
	pthread_mutex_lock(&args->rip_m);
	if (args->rip)
	{
		pthread_mutex_unlock(&args->rip_m);
		return (true);
	}
	pthread_mutex_unlock(&args->rip_m);
	return (false);
}

/*
Waiter is "checking pulse" of every philosopher every 100 microseconds.
*/

void	*waiter(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	while (1)
	{
		if (full_death(args))
			return (0);
		if (starvation_death(args))
			return (0);
	}
	return (0);
}
