/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:15:24 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/19 13:04:24 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while ((int)str[i] >= '0' && (int)str[i] <= '9')
		i++;
	if (i == (int)ft_strlen(str))
		return (true);
	return (false);
}

int	pos_atoi(char *str)
{
	unsigned long long int	result;
	int						i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result > INT_MAX || result == 0)
		return (-1);
	return ((int)result);
}

int	parse(int argc, char **argv, t_args *args)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_numeric(argv[i]) == false || pos_atoi(argv[i]) == -1)
			return (printf("Enter positive numbers < INT_MAX. "), 1);
		i++;
	}
	if (pos_atoi(argv[1]) >= 1 && pos_atoi(argv[1]) <= 200)
		args->num_ph = (unsigned)pos_atoi(argv[1]);
	else
		return (printf("There must be between 1 and 200 philosophers. "), 1);
	args->tt_die = (uint64_t)pos_atoi(argv[2]);
	args->tt_eat = (uint64_t)pos_atoi(argv[3]);
	args->tt_sleep = (uint64_t)pos_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = (unsigned)pos_atoi(argv[5]);
	return (0);
}
