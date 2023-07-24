/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 12:12:23 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_night_watch(t_waiter *waiter)
{
	while (42)
	{
		pthread_mutex_lock(&waiter->dead);
		if (waiter->all_alive == false)
			return (1);
		pthread_mutex_unlock(&waiter->dead);
		pthread_mutex_lock(&waiter->eat);
		if (waiter->sated == true)
			return (0);
		pthread_mutex_unlock(&waiter->eat);
		usleep(250);
	}
	return (0);
}

bool	ft_still_standing(t_waiter *waiter, t_philo *philo, int idx)
{
	time_t	timestamp;

	timestamp = ft_timestamp_in_ms(waiter);
	if (philo[idx].dead == true)
	{
		waiter->all_alive = false;
		return (false);
	}
	if (timestamp - philo[idx].last_meal >= waiter->ms_die)
	{
		philo[idx].dead = true;
		waiter->all_alive = false;
		philo[idx].eating = false;
		philo[idx].thinking = false;
		philo[idx].sleeping = false;
		return (false);
	}
	return (true);
}

/* bool	ft_night_watch(t_waiter *waiter, int idx)
{
	//int	i;

	pthread_mutex_lock(&waiter->dead);
	if (ft_still_standing(waiter, idx) == false || waiter->all_alive == false)
	{
		i = -1;
		while (++i < waiter->param->nb_philo)
			pthread_join(waiter->philo[i].thread, NULL);
		usleep(5000);
		i = -1;
		while (++i < waiter->param->nb_philo)
			pthread_detach(waiter->philo[i].thread);
		//usleep(5000);
		pthread_mutex_unlock(&waiter->dead);
		return (false);
	}
	pthread_mutex_unlock(&waiter->dead);
	return (true);
} */
