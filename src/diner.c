/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 12:41:04 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_join_threads(t_waiter *waiter)
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
		printf(KGRN"join_threads = true\n"RT);
	return (true);
}

bool	ft_death_watch(t_waiter *waiter)
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
		printf(KGRN"death_watch = = false\n"RT);
	return (false);
}

bool	ft_create_threads(t_waiter *waiter)
{
	int	i;

	if (DEBUG)
		printf(KYEL "------- "KGRN"THREADS_CREATION"KYEL" -------\n" RT);
	i = -1;
	pthread_mutex_lock(&waiter->start);
	while (++i < waiter->param->nb_philo)
	{
		waiter->philo[i].last_meal = waiter->start_time;
		if (pthread_create(&waiter->philo[i].thread, NULL, \
			&ft_routine_philos, &waiter->philo[i]))
			return (false);
	}
	pthread_mutex_unlock(&waiter->start);
	if (DEBUG)
		printf(KGRN"create_threads = true\n"RT);
	while (1)
		;
	return (true);
}

int	ft_diner(t_waiter *waiter)
{
	waiter->start_time = ft_get_time();
	if (DEBUG)
	{
		printf(KYEL "---------- "KGRN"START_TIME"KYEL" ----------\n" RT);
		printf("waiter->start_time = %ld ms\n", waiter->start_time);
	}
	if (waiter->param->nb_philo == 1)
	{
		ft_the_one_and_only(waiter);
		return (0);
	}
	else if (ft_create_threads(waiter) == true)
		if (ft_death_watch(waiter) == false)
			if (ft_join_threads(waiter) == true)
				return (0);
	return (1);
}
