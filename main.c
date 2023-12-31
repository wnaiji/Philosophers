/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/31 03:24:16 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pars_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				ft_putendl_fd("Error: argument is not valid", 2);
				exit(EXIT_FAILURE);
			}
			if (argv[i][j] == '+' && (j == 0 || argv[i][j - 1] != ' '))
			{
				if (!(argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				{
					ft_putendl_fd("Error: argument is not valid", 2);
					exit(EXIT_FAILURE);
				}
			}
			j++;
		}
	}
}

static t_arg	*init_arg(char **argv, t_arg *arg)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
			arg->nbr_philo = ft_atoi(argv[i]);
		else if (i == 2)
			arg->time_die = ft_atoi(argv[i]);
		else if (i == 3)
			arg->time_eat = ft_atoi(argv[i]);
		else if (i == 4)
			arg->time_sleep = ft_atoi(argv[i]);
		else if (i == 5)
			arg->nbr_eat = ft_atoi(argv[i]);
		i++;
	}
	return (arg);
}

static void	print_single_philo(t_arg *arg)
{
	printf(TIME"0	"PHILO"1 "FORK END"\n");
	printf(DIE"%d	1 "DIED END"\n", arg->time_die + 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg) * ft_atoi(argv[1]));
	if (!arg)
		return (1);
	if (argc == 5 || argc == 6)
	{
		pars_arg(argv);
		arg = init_arg(argv, arg);
		if (arg->nbr_philo == 1)
			print_single_philo(arg);
		arg->time_start = time_now();
		philo(arg);
	}
	else
	{
		printf("Error: The number of argument is not correct\n");
		printf("\n ./philo [nbr philo] [time to die] \
		[time to eat] [time to sleep]\n");
	}
	free(arg);
	return (0);
}
