/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 07:54:38 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_join_threads(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (i-- >= 0)
	{
		if (waiter->philo[i].thread)
			if (pthread_join(waiter->philo[i].thread, NULL))
				return (false);
	}
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
/* 	while (1)
	; */
	ft_usleep(2500);
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
			if (ft_join_threads(waiter) == true)
				return (0);
	}
	return (1);
}
