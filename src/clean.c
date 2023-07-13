/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/13 14:55:53 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	clean_n_quit(t_waiter *waiter)
{
	if (waiter->param)
		waiter->param = free_null(waiter->param);
	if (waiter->philo)
		waiter->philo = free_null(waiter->philo);
	waiter = free_null(waiter);
}
