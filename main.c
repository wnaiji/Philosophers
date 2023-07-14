/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/14 21:38:23 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (i++ < 5)
	{
		if (pthread_mutex_lock(&philo->phork) == 0
			&& pthread_mutex_lock(philo->phork_r) == 0)
		{
			printf("%d is eating\n", philo->name);
			sleep(philo->arg.time_eat);
			pthread_mutex_unlock(&philo->phork);
			pthread_mutex_unlock(philo->phork_r);
			printf("%d is sleeping\n", philo->name);
			sleep(philo->arg.time_sleep);
		}
		else
			printf("%d is thinking\n", philo->name);
	}
	return (NULL);
}

void	create_thread(t_arg arg)
{
	int			i;
	t_philo		philo[arg.nbr_philo];

	i = 0;
	while (i < arg.nbr_philo)
	{
		pthread_mutex_init(&philo[i].phork, NULL);
		philo[i].name = i + 1;
		philo[i].arg = arg;
		philo[i].phork_r = &philo[(i + 1) % arg.nbr_philo].phork;
		pthread_create(&(philo[i].th), NULL, routine, &(philo[i]));
		i++;
	}
	i = 0;
	while (i < arg.nbr_philo)
	{
		pthread_join(philo[i].th, NULL);
		pthread_mutex_destroy(&philo[i].phork);
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
