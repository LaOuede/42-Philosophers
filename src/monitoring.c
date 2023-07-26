/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 11:26:40 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_monitoring(t_philo *philo, time_t limit)
{
	time_t	time;

	time = ft_timestamp_in_ms(philo);
	while (time < limit)
	{
		if (ft_timestamp_in_ms(philo) > philo->last_meal)
		{
			philo->am_i_dead = true;
			if (ft_print_msg(philo, DIED) == 1)
				return (false);
		}
		usleep(100);
		time = ft_timestamp_in_ms(philo);
	}
	return (true);
}

bool	ft_think_n_fork_monitoring(t_philo *philo)
{
	time_t	time;

	time = ft_timestamp_in_ms(philo);
	while (ft_take_forks(philo) == false)
	{
		if (time > philo->last_meal)
		{
			philo->am_i_dead = true;
			if (ft_print_msg(philo, DIED) == 1)
				return (false);
		}
		usleep(100);
		time = ft_timestamp_in_ms(philo);
	}
	return (true);
}
