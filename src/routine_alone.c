/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 10:09:58 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_routine_philo_alone(void *arg)
{
	t_waiter	*waiter;

	(void) arg;
	waiter = ft_init_waiter();
	ft_print_msg(waiter, 0, FORK);
	ft_usleep(waiter->param->ms_die);
	ft_print_msg(waiter, 0, DIED);
	return (0);
}

int	ft_the_one_and_only(t_waiter *waiter)
{
	if (pthread_create(&waiter->philo[0].thread, NULL, \
		&ft_routine_philo_alone, NULL))
		return (1);
	pthread_join(waiter->philo[0].thread, NULL);
	return (0);
}
