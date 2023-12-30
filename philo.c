/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:53:07 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/30 15:55:09 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->global_lock);
	printf(TIME"%d	"PHILO"%d "FORK END"\n", time_now(), philo->name);
	pthread_mutex_unlock(&philo->arg->global_lock);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->global_lock);
	printf(TIME"%d	"PHILO"%d "FORK END"\n", \
	time_now(), philo->name);
	printf(TIME"%d	"PHILO"%d "EAT END"\n", \
	time_now(), philo->name);
	pthread_mutex_unlock(&philo->arg->global_lock);
	philo->meal++;
	ft_usleep(philo, philo->arg->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_r);
}

void	death(t_philo *philo)
{
	if (is_died(philo) == true)
	{
		pthread_mutex_lock(&philo->arg->global_lock);
		printf(DIE"%d	%d "DIED END"\n", time_now(), philo->name);
		pthread_detach(philo->th);
		exit(EXIT_FAILURE);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->name % 2 == 0)
		ft_usleep(philo, philo->arg->time_eat / 3);
	while (1)
	{
		if (pthread_mutex_lock(&philo->fork) == 0)
		{
			pthread_mutex_lock(&philo->arg->global_lock);
			printf(TIME"%d	"PHILO"%d "FORK END"\n", time_now(), philo->name);
			pthread_mutex_unlock(&philo->arg->global_lock);
			if (pthread_mutex_lock(philo->fork_r) == 0)
			{
				pthread_mutex_lock(&philo->arg->global_lock);
				printf(TIME"%d	"PHILO"%d "FORK END"\n", \
				time_now(), philo->name);
				printf(TIME"%d	"PHILO"%d "EAT END"\n", \
				time_now(), philo->name);
				pthread_mutex_unlock(&philo->arg->global_lock);
				philo->meal++;
				ft_usleep(philo, philo->arg->time_eat);
				pthread_mutex_unlock(&philo->fork);
				pthread_mutex_unlock(philo->fork_r);
			}
			if (is_died(philo) == true)
			{
				pthread_mutex_lock(&philo->arg->global_lock);
				printf(DIE"%d	%d "DIED END"\n", time_now(), philo->name);
				pthread_detach(philo->th);
				exit(EXIT_FAILURE);
			}
			else
				philo->end_last_eat = time_now();
			if (philo->meal == philo->arg->nbr_eat)
				return (NULL);
			pthread_mutex_lock(&philo->arg->global_lock);
			printf(TIME"%d	"PHILO"%d "SLEEP END"\n", time_now(), philo->name);
			pthread_mutex_unlock(&philo->arg->global_lock);
			ft_usleep(philo, philo->arg->time_sleep);
			if (is_died(philo) == true)
			{
				pthread_mutex_lock(&philo->arg->global_lock);
				printf(DIE"%d	%d "DIED END"\n", time_now(), philo->name);
				pthread_detach(philo->th);
				exit(EXIT_FAILURE);
			}
		}
		else if (is_died(philo) == false)
		{
			pthread_mutex_lock(&philo->arg->global_lock);
			printf(TIME"%d	"PHILO"%d "THINK END"\n", time_now(), philo->name);
			pthread_mutex_unlock(&philo->arg->global_lock);
		}
		else
		{
			pthread_mutex_lock(&philo->arg->global_lock);
			printf(DIE"%d	%d "DIED END"\n", time_now(), philo->name);
			pthread_detach(philo->th);
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

void	philo(t_arg *arg)
{
	int				index;
	t_philo			*philo;

	index = 0;
	pthread_mutex_init(&arg->global_lock, NULL);
	philo = malloc(sizeof(t_philo) * arg->nbr_philo);
	if (!philo)
		return ;
	while (1)
	{
		if (time_now() == 0)
		{
			while (index < arg->nbr_philo)
			{
				pthread_mutex_init(&philo[index].fork, NULL);
				philo[index] = init_philo(philo[index], arg, index);
				philo[index].fork_r = &philo[(index + 1) % arg->nbr_philo].fork;
				pthread_create(&(philo[index].th), NULL, \
				routine, &(philo[index]));
				index++;
			}
		}
		if (index > 0)
			break ;
	}
	while (--index >= 0)
		pthread_join(philo[index].th, NULL);
	while (index++ < arg->nbr_philo)
		pthread_mutex_destroy(&(philo[index].fork));
	free(philo);
}
