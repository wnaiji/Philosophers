/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:53:07 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/15 22:20:56 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_thread(t_philo *philo, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.nbr_philo)
	{
		pthread_join(philo[i].th, NULL);
		pthread_mutex_destroy(&philo[i].phork);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	is_dead(t_philo philo, t_arg arg)
{
	long int	real_time;

	real_time = time_now() - philo.end_last_eat;
	if (real_time > philo.arg.time_die)
	{
		printf("%ld %d died\n", time_now(), philo.name);
		arg.dead = 1;
	}
}

t_philo	*eating_and_sleeping(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", time_now(), philo->name);
	printf("%ld %d has taken a fork\n", time_now(),philo->name);
	printf("%ld %d is eating\n", time_now(), philo->name);
	usleep(philo->arg.time_eat);
	pthread_mutex_unlock(&philo->phork);
	pthread_mutex_unlock(philo->phork_r);
	printf("%ld %d is sleeping\n", time_now(), philo->name);
	usleep(philo->arg.time_sleep);
	return (philo);
}

void	*routine(void *arg)
{
	t_philo 		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (pthread_mutex_lock(&philo->phork) == 0
			&& pthread_mutex_lock(philo->phork_r) == 0)
		{
			philo = eating_and_sleeping(philo);
			philo->end_last_eat = time_now();
		}
		printf("%ld %d is thinking\n", time_now(), philo->name);
		is_dead(*philo, philo->arg);
		if (philo->arg.dead == 1)
			break ;
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
	destroy_thread(philo, arg);
}
