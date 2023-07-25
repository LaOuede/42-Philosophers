/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 10:09:32 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//TODO : fix eat_monitoring and add sleep_monitoring
// (see if it is possible to do only 1 function)

// TODO : add a condition (if TTE > TTD or TTS > TTD) ?
// Don't think monitoring is needed if TTE < TTD
bool	ft_eat_monitoring(t_philo *philo, time_t limit)
{
	while (ft_timestamp_in_ms(philo) < limit)
	{
		if (ft_timestamp_in_ms(philo) > philo->last_meal)
		{
			philo->am_i_dead = true;
			if (ft_print_msg(philo, DIED) == 1)
			{
				printf("philo[%d] died eating\n", philo->idx);
				return (false);
			}
		}
		usleep(100);
	}
	return (true);
}

bool	ft_sleep_monitoring(t_philo *philo, time_t limit)
{
	time_t	time;

	time = ft_timestamp_in_ms(philo);
	while (ft_timestamp_in_ms(philo) < limit)
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

/* bool	ft_all_sated(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		if (philo[i].meals != philo->nb_meals)
			break ;
		pthread_mutex_lock(philo->mutex_eat);
		philo[i].sated = 1;
		pthread_mutex_unlock(philo->mutex_eat);
		return (true);
	}
	return (false);
} */

/* bool	ft_check_meals(t_philo *philo, int idx)
{
	//printf("philo[%d]\n", idx);
	//printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	philo[idx].meals += 1;
	//printf("philo[%d] meals = %d\n", idx, waiter->philo[idx].meals);
	if (philo[idx].meals >= philo->nb_meals)
	{
		if (ft_all_sated(philo) == true)
			return (false);
	}
	return (true);
} */
