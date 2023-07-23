/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/23 18:05:19 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	ft_clean_n_quit(t_waiter *waiter)
{
	int	i;

	if (waiter->philo)
	{
		i = 0;
		if (waiter->param->nb_philo > 1)
		{
			while (++i < waiter->param->nb_philo)
			{
				pthread_mutex_destroy(&waiter->philo->his_fork.fork);
				pthread_mutex_destroy(&waiter->philo->nbr_fork->fork);
			}
		}
		//ft_join_threads(waiter, waiter->philo);
		waiter->philo = ft_free_null(waiter->philo);
	}
	if (waiter->param)
		waiter->param = ft_free_null(waiter->param);
	pthread_mutex_destroy(&waiter->start);
	pthread_mutex_destroy(&waiter->eat);
	pthread_mutex_destroy(&waiter->dead);
	pthread_mutex_destroy(&waiter->print);
	waiter = ft_free_null(waiter);
}
