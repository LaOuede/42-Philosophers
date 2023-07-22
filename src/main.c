/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/22 17:31:23 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// TODO : pb with join because nightwatch detach before!
bool	ft_join_threads(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (++i < waiter->param->nb_philo)
	{
		if (pthread_join(waiter->philo[i].thread, NULL))
			return (false);
	}
	usleep(4000);
	return (true);
}

bool	ft_create_threads(t_waiter *waiter)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&waiter->start);
	while (++i < waiter->param->nb_philo)
	{
		waiter->philo[i].last_meal = waiter->start_time;
		if (pthread_create(&waiter->philo[i].thread, NULL, \
			&ft_routine_philos, &waiter->philo[i]))
			return (false);
	}
	waiter->start_time = ft_get_time();
	pthread_mutex_unlock(&waiter->start);
	return (true);
}

int	ft_diner(t_waiter *waiter)
{
	if (waiter->param->nb_philo == 1)
	{
		ft_the_one_and_only(waiter);
		return (0);
	}
	else
	{
		ft_init_forks(waiter, waiter->philo);
		if (ft_create_threads(waiter) == true)
			while (ft_death_watchtower(waiter) == true)
				continue ;
		if (ft_join_threads(waiter) == true)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_waiter	*waiter;

	waiter = ft_init_waiter();
	if ((argc == 5 || argc == 6) && ft_parsing(argc, argv) == true)
	{
		waiter->param = ft_init_param(argc, argv);
		waiter->philo = ft_init_philo(waiter);
		ft_diner(waiter);
		ft_clean_n_quit(waiter);
	}
	else
		ft_putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
