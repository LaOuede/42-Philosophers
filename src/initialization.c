/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 10:05:37 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo	*ft_init_philo(t_waiter *waiter)
{
	int				i;
	static t_philo	*philo;

	i = 0;
	if (!philo)
	{
		philo = ft_calloc(waiter->param->nb_philo, sizeof(t_philo));
		while (++i < waiter->param->nb_philo)
		{
			philo[i].idx = i;
			philo[i].thread = 0;
			philo[i].eating = 0;
			philo[i].thinking = 0;
			philo[i].sleeping = 0;
			philo[i].dead = 0;
			philo[i].meals = 0;
			philo[i].last_meal = 0;
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
