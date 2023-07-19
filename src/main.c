/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 12:02:32 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_waiter	*waiter;

	waiter = ft_init_waiter();
	if ((argc == 5 || argc == 6) && ft_parsing(argc, argv) == true)
	{
		waiter->param = ft_init_param(argc, argv);
		waiter->philo = ft_init_philo(waiter);
		ft_init_fork(waiter);
		ft_diner(waiter);
		ft_clean_n_quit(waiter);
	}
	else
		ft_putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
