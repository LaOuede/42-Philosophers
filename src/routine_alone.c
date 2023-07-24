/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_alone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 12:37:11 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_routine_philo_alone(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printf("SEGFAULT 1\n");
	printf("nb_philo = %d\n", philo->waiter->nb_philo);
	ft_print_msg_alone(philo->waiter, 0, FORK);
	ft_usleep(philo->waiter->ms_die);
	ft_print_msg_alone(philo->waiter, 0, DIED);
	return (0);
}

int	ft_the_one_and_only(t_waiter *waiter, pthread_t *thread)
{
	waiter->start_time = ft_get_time();
	if (pthread_create(&thread[0], NULL, \
		&ft_routine_philo_alone, NULL))
		return (1);
	pthread_join(thread[0], NULL);
	return (0);
}
