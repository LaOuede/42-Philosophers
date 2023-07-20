/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/20 15:38:29 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_still_standing(t_waiter *waiter, int idx)
{
	time_t	timestamp;

	timestamp = ft_timestamp_in_ms(waiter);
	if (timestamp - waiter->philo[idx].last_meal >= waiter->param->ms_die)
	{
		waiter->philo[idx].dead = true;
		ft_print_msg(waiter, idx, DIED);
		pthread_mutex_lock(&waiter->dead);
		waiter->all_alive = false;
		pthread_mutex_unlock(&waiter->dead);
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
		return (false);
	}
	pthread_mutex_unlock(&waiter->dead);
	return (true);
}
