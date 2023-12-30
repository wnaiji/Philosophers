/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:53:07 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/30 16:28:05 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			take_fork(philo);
			if (pthread_mutex_lock(philo->fork_r) == 0)
				is_eating(philo);
			check_death(philo);
			philo->end_last_eat = time_now();
			if (philo->meal == philo->arg->nbr_eat)
				return (NULL);
			is_sleeping(philo);
			check_death(philo);
		}
		else if (is_died(philo) == false)
			is_thiking(philo);
		check_death(philo);
	}
	return (NULL);
}

void	philo(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	i = -1;
	pthread_mutex_init(&arg->global_lock, NULL);
	philo = malloc(sizeof(t_philo) * arg->nbr_philo);
	if (!philo)
		return ;
	while (1)
	{
		if (time_now() == 0)
		{
			while (++i < arg->nbr_philo)
			{
				pthread_mutex_init(&philo[i].fork, NULL);
				philo[i] = init_philo(philo[i], arg, i);
				philo[i].fork_r = &philo[(i + 1) % arg->nbr_philo].fork;
				pthread_create(&(philo[i].th), NULL, routine, &(philo[i]));
			}
			break ;
		}
	}
	while (--i >= 0)
		pthread_join(philo[i].th, NULL);
	free(philo);
}
