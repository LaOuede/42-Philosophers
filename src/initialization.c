/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/13 14:08:48 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo	*init_philo(t_waiter *waiter)
{
	static t_philo	*philo;

	if (!philo)
		philo = ft_calloc(waiter->param->nb_philo, sizeof(t_philo));
	return (philo);
}

t_param	*init_param(int argc, char **argv)
{
	t_param	*param;

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
		printf(KYEL "--------------------------------\n" RT);
	}
	return (param);
}

t_waiter	*init_waiter(void)
{
	static t_waiter	*waiter = NULL;

	if (!waiter)
	{
		waiter = ft_calloc(1, sizeof(t_waiter));
		waiter->param = NULL;
		waiter->philo = NULL;
		waiter->all_alive = 0;
		waiter->sated = 0;
	}
	return (waiter);
}
