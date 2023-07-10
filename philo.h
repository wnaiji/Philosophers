/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:37 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/10 18:14:22 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_list
{
	pthread_t		th;
	struct s_list	*prev;
	struct s_list	*next;
}			t_list;

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

//Gestion des listes:
//ft_list.c
void	*ft_add_front_list(t_list *list, char *line);
void	*ft_add_back_list(t_list *list, char *line);		//adapter toute les fonction pour les philos
void	*ft_delete_in_head(t_list *list);
char	*ft_last_content(t_list *list);

#endif
