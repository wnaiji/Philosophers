/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:37 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/10 14:05:36 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int	nbr_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nbr_eat;
}			t_arg;

//Outils libft:
//outils_libft.c
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

//Parsing:
//parsing.c
void	check_arg(char **argv);
t_arg	init_arg(char **argv);

#endif
