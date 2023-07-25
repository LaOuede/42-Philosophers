/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 09:37:40 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_init_forks(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
/* 		pthread_mutex_init(philo[i].his_fork.fork, NULL); */
		if (i < philo->nb_philo)
			philo[i].nbr_fork = &philo[i + 1].his_fork;
		if (i == philo->nb_philo - 1)
			philo[i].nbr_fork = &philo[0].his_fork;
		pthread_mutex_init(&philo[i].his_fork.fork, NULL);
	}
	if (DEBUG)
	{
		printf("philo[%d] his fork = %d\n", i, philo[i].his_fork.idx);
		printf("philo[%d] his fork = %p\n", i, &philo[i].his_fork.idx);
		printf("philo[%d] nbr fork = %d\n", i, philo[i].nbr_fork->idx);
		printf("philo[%d] nbr fork = %p\n", i, &philo[i].nbr_fork->idx);
		printf("------------------------\n");
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
		philo[idx].sated = &waiter->sated;
		philo[idx].start_time = &waiter->start_time;
		philo[idx].his_fork.idx = -1;
		philo[idx].eating = false;
		philo[idx].thinking = false;
		philo[idx].sleeping = false;
		philo[idx].meals = 0;
		philo[idx].last_meal = 0;
		philo[idx].time_to_eat = 0;
		philo[idx].time_to_sleep = 0;
		philo[idx].mutex_start = &waiter->start;
		philo[idx].mutex_eat = &waiter->eat;
		philo[idx].mutex_dead = &waiter->dead;
		philo[idx].mutex_print = &waiter->print;
		philo[idx].mutex_forks_lock = &waiter->forks_lock;
	}
	if (DEBUG)
	{
		printf(KYEL "---------- "KGRN"INIT_PHILOS"KYEL" ----------\n" RT);
		printf("idx = %d\n", philo->idx);
		printf("nb_philo = %d\n", philo->nb_philo);
		printf("ms_die = %ld\n", philo->ms_die);
		printf("ms_eat = %ld\n", philo->ms_eat);
		printf("ms_sleep = %ld\n", philo->ms_sleep);
		printf("nb_meals = %d\n", philo->nb_meals);
		printf("am_i_dead = %d\n", philo->am_i_dead);
		printf("sated = %d\n", *philo->sated);
		printf("start_time = %ld\n", *philo->start_time);
		printf("his fork = %d\n", philo->his_fork.idx);
		printf("meals = %d\n", philo->meals);
		printf("last_meal = %ld\n", philo->last_meal);
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
		waiter->nb_meals = -1;
	waiter->start_time = 0;
	pthread_mutex_init(&waiter->start, NULL);
	pthread_mutex_init(&waiter->eat, NULL);
	pthread_mutex_init(&waiter->dead, NULL);
	pthread_mutex_init(&waiter->print, NULL);
	pthread_mutex_init(&waiter->forks_lock, NULL);
	waiter->all_alive = true;
	waiter->sated = false;
	if (DEBUG)
	{
		printf(KYEL "---------- "KGRN"INIT_WAITER"KYEL" ----------\n" RT);
		printf("nb_philo = %d\n", waiter->nb_philo);
		printf("ms_die = %ld\n", waiter->ms_die);
		printf("ms_eat = %ld\n", waiter->ms_eat);
		printf("ms_sleep = %ld\n", waiter->ms_sleep);
		printf("nb_meals = %d\n", waiter->nb_meals);
		printf("all_alive = %d\n", waiter->all_alive);
		printf("sated = %d\n", waiter->sated);
	}
	ft_get_waiter(waiter);
}
