/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:00:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/06 12:45:30 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>   // for INT_MAX
# include <pthread.h>  // for pthread_
# include <stdbool.h>  // for bool
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc, free
# include <string.h>   // for memset
# include <sys/time.h> // for gettimeofday
# include <unistd.h>   // for write, usleep

typedef struct s_ph
{
	unsigned int		id;
	// just array index + 1
	pthread_t			th;
	// philosopher thread
	bool				*l_fork;
	// link to the left fork, true when taken
	bool				*r_fork;
	// same for the right one
	pthread_mutex_t		*l_fork_m;
	// link to the left fork mutex
	pthread_mutex_t		*r_fork_m;
	// same for the right one
	unsigned int		ate;
	// number of times philosopher ate
	pthread_mutex_t		ate_m;
	// corresponding mutex
	unsigned long long	last_meal;
	// start in ms after simulation start
	pthread_mutex_t		last_meal_m;
	// corresponding mutex
	struct s_args		*args;
	// link to global arguments
}						t_ph;

typedef struct s_args
{
	unsigned int		num_ph;
	// number of philosophers
	unsigned long long	tt_die;
	// time to die in ms
	unsigned long long	tt_eat;
	// time to eat in ms
	unsigned long long	tt_sleep;
	// time to sleep in ms
	unsigned int		must_eat;
	// times all must eat for simulation to stop
	struct s_ph			*phs;
	// philosophers' array
	pthread_t			waiter_th;
	// waiter thread (simulation monitor)
	unsigned long long	sim_start;
	// simulation start
	bool				*forks;
	// forks' array
	pthread_mutex_t		*mtx_forks;
	// forks' mutexes array
	bool				rip;
	// simulation must stop
	pthread_mutex_t		rip_m;
	// corresponding mutex
	pthread_mutex_t		print_m;
	// mutex for printf
}						t_args;

/*		PARSE		*/
size_t					ft_strlen(char *str);
bool					is_numeric(char *str);
int						pos_atoi(char *str);
int						parse(int argc, char **argv, t_args *args);
/*		UTILS		*/
unsigned long long		current_time(void);
bool					custom_sleep(unsigned long long ms, t_args *args);
void					free_args(t_args *args);
void					print_state(t_ph *ph, char *msg);
/*		MAIN		*/
int						init(int argc, char **argv, t_args *args,
							unsigned int i);
void					init_phs(t_args *args, unsigned int i,
							unsigned int phs);
/*		THREADS		*/
int						create_threads(t_args *args);
int						join_threads(t_args *args);
/*		LIFE		*/
void					take_forks(t_ph *ph);
void					lock_forks(pthread_mutex_t *left,
							pthread_mutex_t *right);
void					unlock_forks(pthread_mutex_t *left,
							pthread_mutex_t *right);
void					*life(void *arg);
/* 		PULSE CHECK	*/
bool					full_death(t_args *args);
bool					starvation_death(t_args *args);
bool					someone_rip(t_args *args);
int						waiter(void *arg);

#endif