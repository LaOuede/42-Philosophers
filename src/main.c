/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 11:23:40 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_create_threads(t_waiter *waiter, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	pthread_mutex_lock(philo->mutex_start);
	while (++i < philo->nb_philo)
	{
		philo[i].last_meal = *philo->start_time;
		if (pthread_create(&thread[i], NULL, \
			&ft_routine_philos, &philo[i]))
			return (i);
	}
	waiter->start_time = ft_get_time();
	pthread_mutex_unlock(philo->mutex_start);
	return (-1);
}

int	ft_diner(t_waiter *waiter, t_philo *philo)
{
	int			res;
	pthread_t	philo_thread[200];

	if (philo->nb_philo == 1)
	{
		waiter->start_time = ft_get_time();
		ft_the_one_and_only(philo, philo_thread);
		return (0);
	}
	else
	{
		ft_init_forks(philo);
		res = ft_create_threads(waiter, philo, philo_thread);
		if (res >= 0)
			(ft_kill_threads(philo_thread, res));
		if (ft_join_threads(philo, philo_thread) == true)
			return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;
	t_philo		philo[200];

	if ((argc == 5 || argc == 6) && ft_parsing(argc, argv) == true)
	{
		ft_init_waiter(&waiter, argc, argv);
		ft_init_philo(&waiter, philo);
		ft_diner(&waiter, philo);
		ft_destroy_mutex(&waiter, philo);
	}
	else
		ft_putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
