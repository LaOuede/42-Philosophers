/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 10:46:18 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_death_watchtower(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->dead);
	if (waiter->all_alive == false)
		return (false);
	pthread_mutex_unlock(&waiter->dead);
	return (true);
}

bool	ft_still_standing(t_waiter *waiter, int idx)
{
	time_t	timestamp;

	timestamp = ft_timestamp_in_ms(waiter);
	if (timestamp - waiter->philo[idx].last_meal >= waiter->param->ms_die)
	{
		waiter->philo[idx].dead = true;
		waiter->all_alive = false;
		waiter->philo[idx].eating = false;
		waiter->philo[idx].thinking = false;
		waiter->philo[idx].sleeping = false;
		return (false);
	}
	return (true);
}

bool	ft_night_watch(t_waiter *waiter, int idx)
{
	int	i;

	pthread_mutex_lock(&waiter->dead);
	if (ft_still_standing(waiter, idx) == false || waiter->all_alive == false)
	{
		i = -1;
		while (++i < waiter->param->nb_philo)
			pthread_detach(waiter->philo[i].thread);
		pthread_mutex_unlock(&waiter->dead);
		return (false);
	}
	pthread_mutex_unlock(&waiter->dead);
	return (true);
}
