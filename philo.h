/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:37 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/20 16:56:43 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_arg
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	pthread_mutex_t	mdead;
	int				dead;
}			t_arg;

typedef struct s_philo
{
	int				name;
	long int		end_last_eat;
	pthread_mutex_t	phork;
	pthread_mutex_t	*phork_r;
	pthread_t		th;
	t_arg			*arg;
	int				meal;
}			t_philo;

//Outils:
//outils.c
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long int	time_now(void);
int			ft_usleep(long int time);

//Parsing:
//parsing.c
void		check_arg(char **argv);
t_arg		*init_arg(char **argv, t_arg **arg);

//Création des philos:
//philo.c
void		*routine(void *arg);
void		create_thread(t_arg **arg);
//t_philo		*eating_and_sleeping(t_philo *philo);
t_philo		*is_dead(t_philo *philo);
void		destroy_thread(t_philo *philo, t_arg **arg);


#endif
