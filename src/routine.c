;/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/18 09:30:24 by gle-roux         ###   ########.fr       */
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

	param = init_param(0, 0);
	(void) arg;
	printf("The one and only has been created!\n");
	printf("param->ms_die = %d\n", param->ms_die);
	usleep(param->ms_die);
	printf("I'm dead now...\n");
	return (0);
}

int	the_one_and_only(t_waiter *waiter)
{
	if (DEBUG)
		printf(KYEL "----------- "KGRN"ONE_PHILO"KYEL"-----------\n" RT);
	if (pthread_create(&waiter->philo[0].thread, NULL, \
		&routine_philo_alone, NULL))
		return (1);
	pthread_join(waiter->philo[0].thread, NULL);
	return (0);
}
