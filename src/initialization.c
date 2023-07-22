/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/22 16:02:05 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_init_forks(t_waiter *waiter, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < waiter->param->nb_philo)
	{
		philo[i].his_fork.idx = -1;
		pthread_mutex_init(&philo[i].his_fork.fork, NULL);
/* 		printf("i = %d\n", i);
		printf("philo = %d\n", waiter->param->nb_philo - 1); */
		if (i < waiter->param->nb_philo)
			philo[i].nbr_fork = &philo[i + 1].his_fork;
		if (i == waiter->param->nb_philo - 1)
		{
			//printf("0 = %d\n", philo[0].his_fork.idx);
			philo[i].nbr_fork = &philo[0].his_fork;
		}
/* 		printf("value his %d = %d\n", i, philo[i].his_fork.idx);
		printf("value nbr %d = %d\n", i, philo[i].nbr_fork->idx); */
		pthread_mutex_init(&philo[i].nbr_fork->fork, NULL);
	}
}

// TODO : philos must have numbers between 1 and n (don't start at 0)
t_philo	*ft_init_philo(t_waiter *waiter)
{
	int				idx;
	static t_philo	*philo;

	idx = -1;
	if (!philo)
	{
		philo = ft_calloc(waiter->param->nb_philo, sizeof(t_philo));
		while (++idx < waiter->param->nb_philo)
		{
			philo[idx].idx = idx;
			philo[idx].thread = 0;
			philo[idx].eating = false;
			philo[idx].thinking = false;
			philo[idx].sleeping = false;
			philo[idx].his_fork.idx = -1;
			philo[idx].dead = false;
			philo[idx].meals = 0;
			philo[idx].last_meal = 0;
			philo[idx].will_be_dead = waiter->param->ms_die;
		}
	}
	return (philo);
}

t_param	*ft_init_param(int argc, char **argv)
{
	static t_param	*param;

	if (!param)
	{
		param = ft_calloc(1, sizeof(t_param));
		param->nb_philo = ft_atoi(argv[1]);
		param->ms_die = ft_atoi(argv[2]);
		param->ms_eat = ft_atoi(argv[3]);
		param->ms_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			param->nb_meals = ft_atoi(argv[5]);
		else
			param->nb_meals = -1;
		if (DEBUG)
		{
			printf(KYEL "---------- "KGRN"INIT_PARAM"KYEL"----------\n" RT);
			printf(" * param->nb_philo = %d\n", param->nb_philo);
			printf(" * param->ms_die = %ld\n", param->ms_die);
			printf(" * param->ms_eat = %ld\n", param->ms_eat);
			printf(" * param->ms_sleep = %ld\n", param->ms_sleep);
			printf(" * param->nb_meals = %d\n", param->nb_meals);
		}
	}
	return (param);
}

t_waiter	*ft_init_waiter(void)
{
	static t_waiter	*waiter = NULL;

	if (!waiter)
	{
		waiter = ft_calloc(1, sizeof(t_waiter));
		waiter->start_time = 0;
		waiter->param = NULL;
		waiter->philo = NULL;
		pthread_mutex_init(&waiter->start, NULL);
		pthread_mutex_init(&waiter->eat, NULL);
		pthread_mutex_init(&waiter->dead, NULL);
		pthread_mutex_init(&waiter->print, NULL);
		waiter->all_alive = true;
		waiter->sated = false;
	}
	return (waiter);
}
