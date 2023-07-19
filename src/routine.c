/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 12:42:10 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_forking(int idx)
{
	t_philo	*philo;

	(void)idx;
	philo = ft_init_philo(0);
	pthread_mutex_lock(&philo[idx].his_fork.fork);
	if (philo[idx].his_fork.free == true)
	{
		philo[idx].his_fork.free = false;
		pthread_mutex_unlock(&philo[idx].his_fork.fork);
		return (true);
	}
	pthread_mutex_unlock(&philo[idx].his_fork.fork);
	return (false);
}

void	*ft_routine_philos(void *arg)
{
	int			idx;
	t_waiter	*waiter;

	idx = *(int *)arg;
	waiter = ft_init_waiter();
	pthread_mutex_lock(&waiter->start);
	pthread_mutex_unlock(&waiter->start);
	printf("Philo %d created\n", idx);
	if (ft_forking(idx) == true)
		ft_print_msg(waiter, idx, FORK);
	return (0);
}
