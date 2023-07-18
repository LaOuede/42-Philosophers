/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/18 16:05:33 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_routine_philos(void *arg)
{
	t_philo		*philo;
	t_waiter	*waiter;

	philo = (t_philo *)arg;
	waiter = ft_init_waiter();
	pthread_mutex_lock(&waiter->start);
	pthread_mutex_unlock(&waiter->start);
	printf("Philo %d created\n", philo->idx);
	return (0);
}

void	*ft_routine_philo_alone(void *arg)
{
	time_t		check;
	t_param		*param;

	param = ft_init_param(0, 0);
	(void) arg;
	printf("The one and only has been created!\n");
	ft_usleep(param->ms_die);
	printf("I'm dead now...\n");
	check = ft_timestamp_in_ms();
	printf("death_time = %ld\n", check);
	return (0);
}

int	ft_the_one_and_only(t_waiter *waiter)
{
	if (DEBUG)
		printf(KYEL "----------- "KGRN"ONE_PHILO"KYEL"-----------\n" RT);
	if (pthread_create(&waiter->philo[0].thread, NULL, \
		&ft_routine_philo_alone, NULL))
		return (1);
	pthread_join(waiter->philo[0].thread, NULL);
	return (0);
}
