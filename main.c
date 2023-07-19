/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/19 14:40:48 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	*arg;

	if (argc == 5 || argc == 6)
	{
		check_arg(argv);
		arg = malloc(sizeof(t_arg));
		if (!arg)
			return (1);
		arg = init_arg(argv, arg);
		create_thread(arg);
	}
	else
	{
		(void)arg;
		printf("Error: the number of argument is not correct\n");
	}
	return (0);
}
