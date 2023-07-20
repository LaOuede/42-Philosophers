/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:01 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_check_meals(t_waiter *waiter, int idx)
{
	waiter->philo->meals += 1;
	if (waiter->philo[idx].last_meal == waiter->param->nb_meals)
	{
		pthread_mutex_lock(&waiter->eat);
		waiter->sated = true;
		pthread_mutex_unlock(&waiter->eat);
		return (false);
	}
	return (true);
}
