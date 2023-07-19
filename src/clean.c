/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 12:12:20 by gle-roux         ###   ########.fr       */
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
	//int	i;

	if (waiter->philo)
	{
/* 		i = -1;
		while (++i < waiter->param->nb_philo)
			waiter->philo[i].his_fork = ft_free_null(waiter->philo[i].his_fork); */
		waiter->philo = ft_free_null(waiter->philo);
	}
	if (waiter->param)
		waiter->param = ft_free_null(waiter->param);
	pthread_mutex_destroy(&waiter->print);
	waiter = ft_free_null(waiter);
}
