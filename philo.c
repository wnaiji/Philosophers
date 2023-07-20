/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:53:07 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/20 17:43:21 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_thread(t_philo *philo, t_arg **arg)
{
	int	i;

	i = 0;
	while (i < (*arg)->nbr_philo)
	{
		pthread_join(philo[i].th, NULL);
		pthread_mutex_destroy(&philo[i].phork);
		i++;
	}
		pthread_mutex_destroy(&(*arg)->mdead);
		free(*arg);
		free(philo);
}

t_philo	*is_dead(t_philo *philo)
{
	long int	real_time;

	real_time = time_now() - philo->end_last_eat;
	if (real_time > philo->arg->time_die)
	{
		printf("%ld %d died\n", time_now(), philo->name);
		if (pthread_mutex_lock(&philo->arg->mdead) == 0)
		{
			philo->arg->dead = 1;
			pthread_mutex_unlock(&philo->arg->mdead);
		}
	}
	return (philo);
}

void	*routine(void *arg)
{
	t_philo 		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->end_last_eat != 0)
			philo = is_dead(philo);
		if (philo->arg->dead == 1)
			break ;
		if (pthread_mutex_lock(&philo->phork) == 0
			&& pthread_mutex_lock(philo->phork_r) == 0)
		{
			printf("%ld %d has taken a fork\n", time_now(), philo->name);
			printf("%ld %d has taken a fork\n", time_now(),philo->name);
			printf("%ld %d is eating\n", time_now(), philo->name);
			philo->meal++;
			usleep(philo->arg->time_eat * 1000);
			pthread_mutex_unlock(&philo->phork);
			pthread_mutex_unlock(philo->phork_r);
			philo->end_last_eat = time_now();
			if (philo->meal == philo->arg->nbr_eat || philo->arg->dead == 1)
				break ;
			printf("%ld %d is sleeping\n", time_now(), philo->name);
			usleep(philo->arg->time_sleep * 1000);
		}
		//if (philo->arg->dead == 1)
		//	break ;
		printf("%ld %d is thinking\n", time_now(), philo->name);
	}
	return (NULL);
}

void	create_thread(t_arg **arg)
{
	int			i;
	t_philo		*philo;//[(*arg)->nbr_philo];

	i = 0;
	philo = malloc(sizeof(t_philo) * (*arg)->nbr_philo);
	if (!philo)
		return ;
	while (i < (*arg)->nbr_philo)
	{
		pthread_mutex_init(&philo[i].phork, NULL);
		philo[i].name = i + 1;
		philo[i].arg = *arg;
		philo[i].phork_r = &philo[(i + 1) % (*arg)->nbr_philo].phork;
		philo[i].end_last_eat = time_now();
		pthread_create(&(philo[i].th), NULL, routine, &(philo[i]));
		i++;
	}
	destroy_thread(philo, arg);
	exit(EXIT_SUCCESS);
}

