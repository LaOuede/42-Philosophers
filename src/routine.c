/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/17 16:18:41 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine_philos(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printf("Philo %d created\n", philo->idx);
	return (0);
}

void	*routine_philo_alone(void *arg)
{
	t_param	*param;

	param = (t_param *)arg;
	printf("The one and only has been created!\n");
	usleep(param->ms_die);
	printf("I'm dead now...\n");
	return (0);
}

int	the_one_and_only(t_waiter *waiter)
{
	if (pthread_create(&waiter->philo[0].thread, NULL, \
		&routine_philo_alone, &waiter->param->ms_die))
		return (1);
	return (0);
}

