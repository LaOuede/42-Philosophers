/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 11:19:19 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_monitoring(t_philo *philo, time_t limit)
{
	while (ft_timestamp_in_ms(philo) < limit)
	{
		if (ft_timestamp_in_ms(philo) > philo->last_meal)
		{
			philo->am_i_dead = true;
			ft_print_msg(philo, DIED);
		}
		usleep(100);
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
			ft_print_msg(philo, DIED);
		}
		usleep(100);
		time = ft_timestamp_in_ms(philo);
	}
	return (true);
}
