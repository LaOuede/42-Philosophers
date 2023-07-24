/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 15:21:10 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//TODO : fix eat_monitoring and add sleep_monitoring
// (see if it is possible to do only 1 function)

// TODO : add a condition (if TTE > TTD or TTS > TTD) ?
// Don't think monitoring is needed if TTE < TTD
/* bool	ft_eat_monitoring(t_waiter *waiter, t_philo *philo, time_t limit, int idx)
{
	time_t	time_now;
	time_t	start_action;

	(void)idx;
	time_now = ft_timestamp_in_ms(waiter);
	start_action = ft_timestamp_in_ms(waiter);
	printf("who's here = %d\n", idx);
	printf("time_now = %ld\n", time_now);
	printf("start_action = %ld\n", start_action);
	printf("limit = %ld\n", limit);
	while (time_now - philo[idx].last_meal <= limit)
	{
		//printf("time_now = %ld\n", time_now);
		start_action = time_now - philo[idx].last_meal;
		if (start_action >= waiter->ms_die)
		{
			philo[idx].dead = true;
			if (ft_print_msg(waiter, philo, idx, DIED) == 1)
			{
				printf("TEST\n");
				return (false);
			}
			return (false);
		}
		usleep(100);
		time_now = ft_timestamp_in_ms(waiter);
	}
	return (true);
}

bool	ft_all_sated(t_waiter *waiter, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < waiter->nb_philo)
	{
		if (philo[i].meals != waiter->nb_meals)
			break ;
		pthread_mutex_lock(&waiter->eat);
		waiter->sated = true;
		pthread_mutex_unlock(&waiter->eat);
		return (true);
	}
	return (false);
}

bool	ft_check_meals(t_waiter *waiter, t_philo *philo, int idx)
{
	//printf("philo[%d]\n", idx);
	//printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	philo[idx].meals += 1;
	//printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	if (philo[idx].meals >= waiter->nb_meals)
	{
		if (ft_all_sated(waiter, philo) == true)
			return (false);
	}
	return (true);
} */
