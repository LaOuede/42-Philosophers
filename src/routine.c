/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 12:30:25 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_think(t_waiter *waiter, t_philo *philo, int idx)
{
	philo[idx].thinking = true;
	if (ft_print_msg(waiter, philo, idx, THINK) == 1)
		return (false);
	usleep(250);
	return (true);
}

bool	ft_sleep(t_waiter *waiter, t_philo *philo, int idx)
{
	philo[idx].sleeping = true;
	if (ft_print_msg(waiter, philo, idx, SLEEP) == 1)
		return (false);
	ft_usleep(waiter->ms_sleep);
	return (true);
}

bool	ft_eat(t_waiter *waiter, t_philo *philo, int idx)
{
	if (ft_check_meals(waiter, philo, idx) == true)
	{
		philo[idx].last_meal = ft_timestamp_in_ms(waiter);
		if (ft_print_msg(waiter, philo, idx, EAT))
			return (false);
		if (ft_eat_monitoring(waiter, philo, waiter->ms_eat, idx) == true)
		{
			philo[idx].his_fork.idx = -1;
			philo[idx].nbr_fork->idx = -1;
			pthread_mutex_unlock(&philo[idx].his_fork.fork);
			pthread_mutex_unlock(&philo[idx].nbr_fork->fork);
			return (true);
		}
	}
	return (false);
}

bool	ft_take_forks(t_waiter *waiter, t_philo *philo, int idx)
{
	time_t	time_now;

	time_now = ft_timestamp_in_ms(waiter);
	while (42)
	{
		if (time_now > waiter->ms_die)
			return (false);
		pthread_mutex_lock(&philo[idx].his_fork.fork);
		pthread_mutex_lock(&philo[idx].nbr_fork->fork);
		if (philo[idx].his_fork.idx == -1 \
			&& philo[idx].nbr_fork->idx == -1)
		{
			if (ft_print_msg(waiter, philo, idx, FORK) == 1)
				return (false);
			philo[idx].his_fork.idx = idx;
			if (ft_print_msg(waiter, philo, idx, FORK) == 1)
				return (false);
			philo[idx].nbr_fork->idx = idx;
			return (true);
		}
		pthread_mutex_unlock(&philo[idx].his_fork.fork);
		pthread_mutex_unlock(&philo[idx].nbr_fork->fork);
	}
	return (false);
}

void	*ft_routine_philos(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->waiter->start);
	pthread_mutex_unlock(&philo->waiter->start);
	if (!(philo->idx & 1))
	{
		ft_print_msg(philo->waiter, philo, philo->idx, THINK);
		ft_usleep(philo->waiter->ms_eat / 2);
	}
	while (42)
	{
		if (ft_take_forks(philo->waiter, philo, philo->idx) == false)
			break ;
		if (ft_eat(philo->waiter, philo, philo->idx) == false)
			break ;
		if (ft_sleep(philo->waiter, philo, philo->idx) == false)
			break ;
		if (ft_think(philo->waiter, philo, philo->idx) == false)
			break ;
	}
	return (arg);
}
