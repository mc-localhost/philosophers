/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:49 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/20 16:17:41 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(int argc, char **argv, t_args *args, unsigned int i)
{
	memset(args, 0, sizeof(t_args));
	if (parse(argc, argv, args) == 1)
		return (printf("Check the arguments\n"), 1);
	args->phs = malloc(sizeof(t_ph) * args->num_ph);
	if (!args->phs)
		return (printf("malloc fail\n"), 1);
	args->forks = malloc(sizeof(bool) * args->num_ph);
	if (!args->forks)
		return (free_args(args), printf("malloc fail\n"), 1);
	memset(args->forks, 0, sizeof(bool) * args->num_ph);
	args->mtx_forks = malloc(sizeof(pthread_mutex_t) * args->num_ph);
	if (!args->mtx_forks)
		return (free_args(args), printf("malloc fail\n"), 1);
	while (i < args->num_ph)
	{
		pthread_mutex_init(&args->mtx_forks[i], NULL);
		i++;
	}
	init_phs(args, 0, args->num_ph);
	pthread_mutex_init(&args->rip_m, NULL);
	pthread_mutex_init(&args->print_m, NULL);
	return (0);
}

void	init_phs(t_args *args, unsigned int i, unsigned int phs)
{
	unsigned int	l_fork_i;
	unsigned int	r_fork_i;

	while (i < phs)
	{
		l_fork_i = (i + phs) % phs;
		r_fork_i = (i + 1) % phs;
		memset(&args->phs[i], 0, sizeof(t_ph));
		args->phs[i].id = i + 1;
		args->phs[i].l_fork = &args->forks[l_fork_i];
		args->phs[i].r_fork = &args->forks[r_fork_i];
		args->phs[i].l_fork_m = &args->mtx_forks[l_fork_i];
		args->phs[i].r_fork_m = &args->mtx_forks[r_fork_i];
		args->sim_start = current_time();
		args->phs[i].last_meal = args->sim_start;
		pthread_mutex_init(&args->phs[i].ate_m, NULL);
		pthread_mutex_init(&args->phs[i].last_meal_m, NULL);
		args->phs[i].args = args;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc == 5 || argc == 6)
	{
		if (init(argc, argv, &args, 0) == 1)
			return (1);
		else
		{
			create_threads(&args);
			join_threads(&args);
			free_args(&args);
		}
	}
	else
		return (printf("Wrong number of arguments\n"), 1);
	return (0);
}
