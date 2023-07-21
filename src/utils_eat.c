/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 11:28:14 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
bool	ft_smart_eat(t_waiter *waiter, int idx)
{
	(void)idx;
	if (waiter->param->ms_eat >= waiter->param->ms_die)
	{
		;
	}
	ft_usleep(waiter->param->ms_eat);
	return (true);
}

bool	ft_check_meals(t_waiter *waiter, int idx)
{
	waiter->philo->meals += 1;
	if (waiter->philo[idx].meals == waiter->param->nb_meals)
	{
		pthread_mutex_lock(&waiter->eat);
		waiter->sated = true;
		pthread_mutex_unlock(&waiter->eat);
		return (false);
	}
	return (true);
}
