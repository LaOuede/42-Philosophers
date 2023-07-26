/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 09:00:43 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_dispose_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->his_fork.fork);
	pthread_mutex_lock(&philo->nbr_fork->fork);
	philo->his_fork.idx = -1;
	philo->nbr_fork->idx = -1;
	pthread_mutex_unlock(&philo->his_fork.fork);
	pthread_mutex_unlock(&philo->nbr_fork->fork);
}

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
