/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/13 10:46:44 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("je suis dans le philo %d\n", philo->name);
	return (NULL);
}

void	create_thread(t_arg arg)
{
	int			i;
	pthread_t	th[arg.nbr_philo];

	i = 0;
	while (i < arg.nbr_philo)
	{
		t_philo		*philo;

		philo = malloc(sizeof(t_philo));
		philo->name = i + 1;
		philo->arg = arg;
		pthread_create(&th[i], NULL, routine, (void *)philo);
		i++;
	}
	i = 0;
	while (i <= arg.nbr_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 5 || argc == 6)
	{
		check_arg(argv);
		arg = init_arg(argv);
		create_thread(arg);
	}
	else
	{
		(void)arg;
		printf("Error: the number of argument is not correct\n");
	}
	return (0);
}
