/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 10:44:12 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* bool	ft_forking(t_waiter *waiter, int idx)
{
	pthread_mutex_lock(&waiter->print);
	
} */

void	*ft_routine_philos(void *arg)
{
	int			idx;
	t_waiter	*waiter;

	idx = *(int *)arg;
	waiter = ft_init_waiter();
/* 	pthread_mutex_lock(&waiter->start);
	pthread_mutex_unlock(&waiter->start); */
	printf("Philo %d created\n", idx);
/* 	while (42)
	{
		if (ft_forking(waiter, idx) == true)
			ft_print_msg(waiter, idx, FORK);
	} */
	return (0);
}
