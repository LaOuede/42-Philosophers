/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 16:23:05 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// TODO : pb with join
bool	ft_kill_n_join(t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].his_fork.fork);
		pthread_mutex_destroy(&philo[i].nbr_fork->fork);
	}
	i = -1;
	while (++i < philo->nb_philo)
	{
		if (DEBUG)
			printf("Philo[%d] - join threads\n", i);
		if (pthread_join(thread[i], NULL))
			return (false);
	}
	usleep(4000);
	return (true);
}

bool	ft_create_threads(t_waiter *waiter, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	pthread_mutex_lock(philo->mutex_start);
	while (++i < philo->nb_philo)
	{
		philo[i].last_meal = *philo->start_time;
		if (pthread_create(&thread[i], NULL, \
			&ft_routine_philos, &philo[i]))
			return (false);
	}
	waiter->start_time = ft_get_time();
	pthread_mutex_unlock(philo->mutex_start);
	return (true);
}

int	ft_diner(t_waiter *waiter, t_philo *philo)
{
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
		if (ft_create_threads(waiter, philo, philo_thread) == false)
			return (1);
		if (ft_kill_n_join(philo, philo_thread) == true)
			return (0);
	}
	return (1);
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
		ft_clean_n_quit(&waiter);
	}
	else
		ft_putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
