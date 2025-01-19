/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:03:05 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/19 13:04:29 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* 
Odd numbered philosophers sleep for 1 ms so that the rest can eat.
Philosophers never hold 1 fork — they pick 2 at the same time
if both are available.
If there is only 1 philosopher, he or she cannot actually eat,
so they might as well not try and just wait till they're dead.
*/

void	*life(void *arg)
{
	t_ph		*ph;

	ph = (t_ph *)arg;
	if (ph->id & 1)
		custom_sleep(1);
	while (1)
	{
		if (ph->args->num_ph == 1)
			custom_sleep(10 + ph->args->tt_die);
		if (someone_rip(ph->args))
			break ;
		// lock_forks(ph->l_fork_m, ph->r_fork_m);
		// if (*ph->l_fork == false && *ph->r_fork == false)
		// {
		// 	take_forks(ph);
		// 	unlock_forks(ph->l_fork_m, ph->r_fork_m);
		// 	print_state(ph, "is sleeping");
		// 	custom_sleep(ph->args->tt_sleep);
		// 	print_state(ph, "is thinking");
		// }
		// else
		// 	unlock_forks(ph->l_fork_m, ph->r_fork_m);
	}
	return (0);
}

// void	lock_forks(pthread_mutex_t *left, pthread_mutex_t *right)
// {
// 	pthread_mutex_lock(left);
// 	pthread_mutex_lock(right);
// }

// void	unlock_forks(pthread_mutex_t *left, pthread_mutex_t *right)
// {
// 	pthread_mutex_unlock(right);
// 	pthread_mutex_unlock(left);
// }

void	take_forks(t_ph *ph)
{
	// *ph->l_fork = true;
	print_state(ph, "has taken a fork");
	// *ph->r_fork = true;
	print_state(ph, "has taken a fork");
	// pthread_mutex_lock(&ph->last_meal_m);
	ph->last_meal = current_time();
	// pthread_mutex_unlock(&ph->last_meal_m);
	print_state(ph, "is eating");
	custom_sleep(ph->args->tt_eat);
	// pthread_mutex_lock(&ph->ate_m);
	ph->ate++;
	// pthread_mutex_unlock(&ph->ate_m);
	// *ph->l_fork = false;
	// *ph->r_fork = false;
}
