/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_alone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 18:02:57 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_routine_philo_alone(void *arg)
{
	t_philo		*philo;
	time_t		timestamp;

	philo = (t_philo *)arg;
	timestamp = ft_timestamp_in_ms(philo);
	printf("%ld %d %s\n", timestamp, 1, FORK);
	ft_usleep(philo->ms_die);
	timestamp = ft_timestamp_in_ms(philo);
	printf("%ld %d %s\n", timestamp, 1, DIED);
	return (0);
}

int	ft_the_one_and_only(t_philo *philo, pthread_t *thread)
{
	if (pthread_create(&thread[0], NULL, \
		&ft_routine_philo_alone, &philo[0]))
		return (1);
	pthread_join(thread[0], NULL);
	return (0);
}
