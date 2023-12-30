/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_of_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:09:17 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/30 16:09:52 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

void	check_death(t_philo *philo)
{
	if (is_died(philo) == true)
	{
		pthread_mutex_lock(&philo->arg->global_lock);
		printf(DIE"%d	%d "DIED END"\n", time_now(), philo->name);
		pthread_detach(philo->th);
		exit(EXIT_FAILURE);
	}
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->global_lock);
	printf(TIME"%d	"PHILO"%d "SLEEP END"\n", time_now(), philo->name);
	pthread_mutex_unlock(&philo->arg->global_lock);
	ft_usleep(philo, philo->arg->time_sleep);
}

void	is_thiking(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->global_lock);
	printf(TIME"%d	"PHILO"%d "THINK END"\n", time_now(), philo->name);
	pthread_mutex_unlock(&philo->arg->global_lock);
}
