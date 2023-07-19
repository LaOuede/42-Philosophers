/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 14:30:47 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_think_n_fork(t_waiter *waiter, int idx)
{
	t_philo	*philo;

	(void)idx;
	philo = ft_init_philo(0);
	pthread_mutex_lock(&philo[idx].his_fork.fork);
	if ((idx %2 == 0) && philo[idx].his_fork.free == true)
	{
		philo[idx].his_fork.free = false;
		ft_print_msg(waiter, idx, FORK);
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
	if (ft_think_n_fork(waiter, idx) == true)
		printf(KGRE"Step 1 ok\n"RT);
	return (0);
}
