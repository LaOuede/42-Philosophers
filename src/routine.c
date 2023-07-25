/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 11:53:23 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_forks_lock);
	if (philo->his_fork.idx == -1 && philo->nbr_fork->idx == -1)
	{
		pthread_mutex_lock(&philo->his_fork.fork);
		pthread_mutex_lock(&philo->nbr_fork->fork);
		philo->his_fork.idx = philo->idx;
		philo->nbr_fork->idx = philo->idx;
		ft_print_msg(philo, FORK);
		ft_print_msg(philo, FORK);
		pthread_mutex_unlock(philo->mutex_forks_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->mutex_forks_lock);
	return (false);
}

bool	ft_think(t_philo *philo)
{
	ft_print_msg(philo, THINK);
	ft_think_n_fork_monitoring(philo);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (ft_print_msg(philo, SLEEP))
		return (false);
	philo->time_to_sleep = ft_timestamp_in_ms(philo) + philo->ms_sleep;
	ft_monitoring(philo, philo->time_to_sleep);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (ft_print_msg(philo, EAT))
		return (false);
	philo->time_to_eat = ft_timestamp_in_ms(philo) + philo->ms_eat;
	philo->last_meal = ft_timestamp_in_ms(philo) + philo->ms_die;
	if (ft_monitoring(philo, philo->time_to_eat))
	{
		pthread_mutex_unlock(&philo->his_fork.fork);
		pthread_mutex_unlock(&philo->nbr_fork->fork);
		pthread_mutex_lock(philo->mutex_forks_lock);
		philo->his_fork.idx = -1;
		philo->nbr_fork->idx = -1;
		pthread_mutex_unlock(philo->mutex_forks_lock);
		philo->meals += 1;
		return (true);
	}
	return (false);
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
	while (philo->nb_meals == -1 || philo->meals < philo->nb_meals)
	{
		if (ft_think(philo) == true)
			if (ft_eat(philo) == true)
				if (ft_sleep(philo) == false)
					break ;
		usleep(500);
	}
	return (arg);
}
