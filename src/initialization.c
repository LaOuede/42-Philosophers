/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/20 14:05:53 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_init_forks(t_waiter *waiter, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < waiter->param->nb_philo)
	{
		philo[i].his_fork = ft_init_his_fork();
		if (i < waiter->param->nb_philo)
			philo[i].nbr_fork = &philo[i + 1].his_fork;
		else if (i == waiter->param->nb_philo - 1)
			waiter->philo[i].nbr_fork = &waiter->philo[0].his_fork;
		pthread_mutex_init(&philo[i].nbr_fork->fork, NULL);
	}
}

t_fork	ft_init_his_fork(void)
{
	t_fork	*his_fork;

	his_fork = ft_calloc(1, sizeof(t_fork));
	pthread_mutex_init(&his_fork->fork, NULL);
	his_fork->taken = false;
	return (*his_fork);
}

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
			printf(" * param->ms_die = %d\n", param->ms_die);
			printf(" * param->ms_eat = %d\n", param->ms_eat);
			printf(" * param->ms_sleep = %d\n", param->ms_sleep);
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
