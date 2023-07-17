/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/17 15:05:31 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_waiter	*waiter;

	waiter = init_waiter();
	if ((argc == 5 || argc == 6) && parsing(argc, argv) == true)
	{
		waiter->param = init_param(argc, argv);
		waiter->philo = init_philo(waiter);
		diner(waiter);
		clean_n_quit(waiter);
	}
	else
		putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
