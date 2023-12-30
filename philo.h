/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:37 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/30 16:11:43 by walidnaiji       ###   ########.fr       */
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
# include <stdbool.h>

//////////ACTION PHILO//////////
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "died"
# define FORK "has taken a fork"
# define THINK "is thinking"

//////////COLOR PRINT//////////
# define TIME "\033[0;35m"
# define PHILO "\033[0;36m"
# define DIE "\033[0;41m"
# define END "\033[0m"

//////////ARGUMENT//////////
typedef struct s_arg
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	suseconds_t		time_start;
	pthread_mutex_t	global_lock;
}			t_arg;

//////////PHILO//////////
typedef struct s_philo
{
	int				name;
	suseconds_t		end_last_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_r;
	pthread_t		th;
	t_arg			*arg;
	int				is_alive;
	int				meal;
}			t_philo;

//////////OUTILS LIBFT//////////
//outils.c
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

//////////OUTILS PHILO//////////
//outils_philo.c
t_philo		init_philo(t_philo philo, t_arg *arg, int index);
suseconds_t	time_now(void);
int			is_died(t_philo *philo);
void		ft_usleep(t_philo *philo, int time);

//////////PHILO//////////
//philo.c
void		*routine(void *arg);
void		philo(t_arg *arg);
//actions_of_philo
void		take_fork(t_philo *philo);
void		is_eating(t_philo *philo);
void		check_death(t_philo *philo);
void		is_sleeping(t_philo *philo);
void		is_thiking(t_philo *philo);

#endif
