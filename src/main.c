/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/13 16:37:12 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_threads(t_waiter *waiter)
{
	if (DEBUG)
		printf(KYEL "------- "KGRN"THREADS_CREATION"KYEL" -------\n" RT);
	int	i;

	i = -1;
	pthread_mutex_lock(&waiter->start);
	if (waiter->param->nb_philo == 1)
		the_one_and_only(waiter);
	else
	{
		while (++i < waiter->param->nb_philo)
		{
			if (pthread_create(&waiter->philo[0].thread, NULL, \
				&routine, &waiter->philo[i]))
				return (1);
		}
	}
	while (i-- >= 0)
	{
		if (waiter->philo[i].thread)
			if (pthread_join(waiter->philo[i].thread, NULL))
				return (1);
	}
	pthread_mutex_unlock(&waiter->start);
	pthread_mutex_destroy(&waiter->start);
	return (0);
}

int	main(int argc, char **argv)
{
	t_waiter	*waiter;

	waiter = init_waiter();
	if ((argc == 5 || argc == 6) && parsing(argc, argv) == true)
	{
		waiter->param = init_param(argc, argv);
		waiter->philo = init_philo(waiter);
		create_threads(waiter);
		clean_n_quit(waiter);
	}
	else
		putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
