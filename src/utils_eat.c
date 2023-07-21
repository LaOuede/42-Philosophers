/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 12:41:37 by gle-roux         ###   ########.fr       */
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

bool	ft_all_sated(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (++i < waiter->param->nb_philo)
	{
		if (waiter->philo[i].meals != waiter->param->nb_meals)
			break ;
		pthread_mutex_lock(&waiter->eat);
		waiter->sated = true;
		exit (EXIT_SUCCESS);
/* 		pthread_mutex_unlock(&waiter->eat);
		return (true); */
	}
	return (false);
}

bool	ft_check_meals(t_waiter *waiter, int idx)
{
	printf("philo[%d]\n", idx);
	printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	waiter->philo[idx].meals += 1;
	printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	if (waiter->philo[idx].meals == waiter->param->nb_meals)
		if (ft_all_sated(waiter) == true)
			return (false);
	return (true);
}
