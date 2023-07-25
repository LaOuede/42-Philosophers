/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 16:52:06 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_init_forks(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		if (i < philo->nb_philo)
			philo[i].nbr_fork = &philo[i + 1].his_fork;
		if (i == philo->nb_philo - 1)
			philo[i].nbr_fork = &philo[0].his_fork;
		pthread_mutex_init(&philo[i].his_fork.fork, NULL);
	}
}

// TODO : philos must have numbers between 1 and n (don't start at 0)
void	ft_init_philo(t_waiter *waiter, t_philo *philo)
{
	int	idx;

	idx = -1;
	while (++idx < waiter->nb_philo)
	{
		philo[idx].idx = idx;
		philo[idx].nb_philo = waiter->nb_philo;
		philo[idx].ms_die = waiter->ms_die;
		philo[idx].ms_eat = waiter->ms_eat;
		philo[idx].ms_sleep = waiter->ms_sleep;
		philo[idx].nb_meals = waiter->nb_meals;
		philo[idx].am_i_dead = false;
		philo[idx].start_time = &waiter->start_time;
		philo[idx].his_fork.idx = -1;
		philo[idx].meals = 0;
		philo[idx].last_meal = 0;
		philo[idx].time_to_eat = 0;
		philo[idx].time_to_sleep = 0;
		philo[idx].mutex_start = &waiter->start;
		philo[idx].mutex_print = &waiter->print;
		philo[idx].mutex_forks_lock = &waiter->forks_lock;
	}
}

void	ft_init_waiter(t_waiter *waiter, int argc, char **argv)
{
	waiter->nb_philo = ft_atoi(argv[1]);
	waiter->ms_die = ft_atoi(argv[2]);
	waiter->ms_eat = ft_atoi(argv[3]);
	waiter->ms_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		waiter->nb_meals = ft_atoi(argv[5]);
	else
		waiter->nb_meals = INT_MAX;
	waiter->start_time = 0;
	pthread_mutex_init(&waiter->start, NULL);
	pthread_mutex_init(&waiter->print, NULL);
	pthread_mutex_init(&waiter->forks_lock, NULL);
	waiter->all_alive = true;
	ft_get_waiter(waiter);
}
