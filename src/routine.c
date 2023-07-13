/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/13 15:05:46 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	pthread_mutex_t	init;
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_init(&init, NULL);
	pthread_mutex_lock(&init);
	printf("Philo %d created\n", philo->idx);
	pthread_mutex_unlock(&init);
	pthread_mutex_destroy(&init);
	return (0);
}

void	*routine_alone(void *arg)
{
	(void) arg;
	printf("The one and only has been created!\n");
	return (0);
}

int	the_one_and_only(t_waiter *waiter)
{
	if (pthread_create(&waiter->philo[0].thread, NULL, &routine_alone, NULL))
		return (1);
	usleep(waiter->param->ms_die);
	printf("I'm dead now...\n");
	return (0);
}

