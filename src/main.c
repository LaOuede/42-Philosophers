/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/13 15:06:33 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_threads(t_waiter *waiter)
{
	printf(KYEL "------- "KGRN"THREADS_CREATION"KYEL" -------\n" RT);
	int	i;

	i = -1;
	if (waiter->param->nb_philo == 1)
		the_one_and_only(waiter);
	while (++i < waiter->param->nb_philo)
	{
		if (pthread_create(&waiter->philo[0].thread, NULL, &routine, &waiter->philo[i]))
			return (1);
	}
	return (0);
}

void	create_philos(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (++i < waiter->param->nb_philo)
	{
		waiter->philo[i].idx = i;
		waiter->philo[i].eating = 0;
		waiter->philo[i].thinking = 0;
		waiter->philo[i].sleeping = 0;
		waiter->philo[i].dead = 0;
		waiter->philo[i].meals = 0;
	}
}

int	main(int argc, char **argv)
{
	t_waiter	*waiter;

	waiter = init_waiter();
	if ((argc == 5 || argc == 6) && parsing(argc, argv) == true)
	{
		waiter->param = init_param(argc, argv);
		waiter->philo = init_philo(waiter);
		create_philos(waiter);
		create_threads(waiter);
		clean_n_quit(waiter);
	}
	else
		putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
