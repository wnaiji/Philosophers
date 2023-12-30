/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:53 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/30 15:09:24 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(t_philo philo, t_arg *arg, int index)
{
	philo.name = index + 1;
	philo.arg = arg;
	philo.end_last_eat = 0;
	philo.meal = 0;
	philo.is_alive = true;
	return (philo);
}

suseconds_t	time_now(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
		ft_putendl_fd("Error: gettimeofday", 2);
	return (now.tv_usec / 1000);
}

int	is_died(t_philo *philo)
{
	suseconds_t	real_time;

	real_time = time_now() - philo->end_last_eat;
	if (real_time > philo->arg->time_die)
		return (true);
	return (false);
}

void	ft_usleep(t_philo *philo, int time)
{
	int	index;

	index = 0;
	while (index < time && is_died(philo) == false)
	{
		usleep(800);
		index++;
	}
}
