/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/17 20:22:36 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	join_threads(t_waiter *waiter)
{
	int	i;

	if (DEBUG)
		printf(KYEL "--------- "KGRN"JOIN_THREADS"KYEL" ---------\n" RT);
	i = -1;
	while (i-- >= 0)
	{
		if (waiter->philo[i].thread)
			if (pthread_join(waiter->philo[i].thread, NULL))
				return (false);
	}
	if (DEBUG)
		printf(KGRN"True\n"RT);
	return (true);
}

bool	death_flag(t_waiter *waiter)
{
	int	i;

	if (DEBUG)
		printf(KYEL "---------- "KGRN"DEATH_FLAG"KYEL" ----------\n" RT);
	pthread_mutex_lock(&waiter->dead);
	if (DEBUG)
		printf("waiter->all_alive = %d\n", waiter->all_alive);
	if (waiter->all_alive == false)
	{
		i = -1;
		while (++i < waiter->param->nb_philo)
			pthread_detach(waiter->philo[i].thread);
		return (true);
	}
	pthread_mutex_unlock(&waiter->dead);
	if (DEBUG)
		printf(KGRN"False\n"RT);
	return (false);
}

bool	create_threads(t_waiter *waiter)
{
	int	i;

	if (DEBUG)
		printf(KYEL "------- "KGRN"THREADS_CREATION"KYEL" -------\n" RT);
	i = -1;
	pthread_mutex_lock(&waiter->start);
	while (++i < waiter->param->nb_philo)
	{
		if (pthread_create(&waiter->philo[0].thread, NULL, \
			&routine_philos, &waiter->philo[i]))
			return (false);
	}
	pthread_mutex_unlock(&waiter->start);
	pthread_mutex_destroy(&waiter->start);
	if (DEBUG)
		printf(KGRN"True\n"RT);
	return (true);
}

int	diner(t_waiter *waiter)
{
	gettimeofday(waiter->start_time, NULL);
	if (DEBUG)
		print_time();
	if (waiter->param->nb_philo == 1)
	{
		the_one_and_only(waiter);
		return (0);
	}
	else if (create_threads(waiter) == true)
		if (death_flag(waiter) == false)
			if (join_threads(waiter) == true)
				return (0);
	return (1);
}
