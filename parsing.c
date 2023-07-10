/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:53 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/10 14:05:48 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[++i])
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: argument is not valid\n");
				exit(EXIT_FAILURE);
			}
			if (argv[i][j] == '+' && argv[i][j - 1] != ' ')
			{
				if (!(argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				{
					printf("Error: argument is not valid\n");
					exit(EXIT_FAILURE);
				}
			}
			j++;
		}
	}
}

t_arg	init_arg(char **argv)
{
	int		i;
	t_arg	arg;

	i = 1;
	while (argv[i])
	{
		if (i == 2)
			arg.nbr_philo = ft_atoi(argv[i]);
		else if (i == 3)
			arg.time_die = ft_atoi(argv[i]);
		else if (i == 4)
			arg.time_eat = ft_atoi(argv[i]);
		else if (i == 5)
			arg.time_sleep = ft_atoi(argv[i]);
		else if (i == 6)
			arg.nbr_eat = ft_atoi(argv[i]);
		i++;
	}
	return (arg);
}
