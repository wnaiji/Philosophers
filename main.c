/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:51:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/10 16:13:30 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 5)
	{
		check_arg(argv);
		arg = init_arg(argv);
	}
	else if (argc == 6)
	{
		check_arg(argv);
		arg = init_arg(argv);
	}
	return (0);
}
