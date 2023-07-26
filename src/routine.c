/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 10:05:56 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_sleep(t_philo *philo)
{
	if (ft_print_msg(philo, SLEEP) == 1)
		return (false);
	philo->time_to_sleep = ft_timestamp_in_ms(philo) + philo->ms_sleep;
	if (ft_monitoring(philo, philo->time_to_sleep) == false)
		return (false);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (ft_print_msg(philo, EAT) == 1)
		return (false);
	philo->time_to_eat = ft_timestamp_in_ms(philo) + philo->ms_eat;
	philo->last_meal = ft_timestamp_in_ms(philo) + philo->ms_die;
	if (ft_monitoring(philo, philo->time_to_eat) == true)
	{
		ft_dispose_forks(philo);
		philo->meals += 1;
		return (true);
	}
	else
		ft_dispose_forks(philo);
	return (false);
}

bool	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->his_fork.fork);
	pthread_mutex_lock(&philo->nbr_fork->fork);
	if (philo->his_fork.idx == -1 && philo->nbr_fork->idx == -1)
	{
		philo->his_fork.idx = philo->idx;
		philo->nbr_fork->idx = philo->idx;
		pthread_mutex_unlock(&philo->his_fork.fork);
		pthread_mutex_unlock(&philo->nbr_fork->fork);
		if (ft_print_msg_forks(philo, FORK) == 1)
			return (false);
		return (true);
	}
	pthread_mutex_unlock(&philo->his_fork.fork);
	pthread_mutex_unlock(&philo->nbr_fork->fork);
	return (false);
}

bool	ft_think(t_philo *philo)
{
	if (ft_print_msg(philo, THINK) == 1)
		return (false);
	if (ft_think_n_fork_monitoring(philo) == false)
		return (false);
	return (true);
}

void	*ft_routine_philos(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex_start);
	pthread_mutex_unlock(philo->mutex_start);
	philo->last_meal = philo->ms_die;
	if (!(philo->idx & 1))
		ft_usleep(philo->ms_eat / 2);
	while (philo->meals < philo->nb_meals)
	{
		if (ft_think(philo) == false)
			break ;
		if (ft_eat(philo) == false)
			break ;
		if (philo->meals == philo->nb_meals)
			break ;
		if (ft_sleep(philo) == false)
			break ;
		usleep(500);
	}
	return (arg);
}
