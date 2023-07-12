/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/12 15:21:39 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_param(t_param *param, int argc, char **argv)
{
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
		printf("param->nb_philo = %d\n", param->nb_philo);
		printf("param->ms_die = %d\n", param->ms_die);
		printf("param->ms_eat = %d\n", param->ms_eat);
		printf("param->ms_sleep = %d\n", param->ms_sleep);
		printf("param->nb_meals = %d\n", param->nb_meals);
	}
}
