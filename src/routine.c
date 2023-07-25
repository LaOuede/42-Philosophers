/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 10:08:17 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* bool	ft_think(t_philo *philo)
{
	if (ft_print_msg(philo, THINK) == 1)
		return (false);
	usleep(500);
	return (true);
} */

bool	ft_think(t_philo *philo)
{
	ft_print_msg(philo, THINK);
	//printf("philo_last_meal = %ld\n", philo->last_meal);
	ft_think_n_fork_monitoring(philo);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (ft_print_msg(philo, SLEEP))
		return (false);
	philo->time_to_sleep = ft_timestamp_in_ms(philo) + philo->ms_sleep;
	ft_sleep_monitoring(philo, philo->time_to_sleep);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (ft_print_msg(philo, EAT))
		return (false);
	philo->time_to_eat = ft_timestamp_in_ms(philo) + philo->ms_eat;
	philo->last_meal = ft_timestamp_in_ms(philo) + philo->ms_die;
	if (ft_eat_monitoring(philo, philo->time_to_eat))
	{
		pthread_mutex_unlock(&philo->his_fork.fork);
		pthread_mutex_unlock(&philo->nbr_fork->fork);
		pthread_mutex_lock(philo->mutex_forks_lock);
		philo->his_fork.idx = -1;
		philo->nbr_fork->idx = -1;
		pthread_mutex_unlock(philo->mutex_forks_lock);
		return (true);
	}
	return (false);
}

/* bool	ft_take_forks(t_philo *philo)
{
	while (42)
	{
		pthread_mutex_lock(&philo->his_fork.fork);
		pthread_mutex_lock(&philo->nbr_fork->fork);
		if (ft_timestamp_in_ms(philo) > philo->ms_die)
			return (false);
		if (philo->his_fork.idx == -1 && philo->nbr_fork->idx == -1)
		{
			philo->his_fork.idx = philo->idx;
			if (ft_print_msg(philo, FORK) == 1)
				return (false);
			philo->nbr_fork->idx = philo->idx;
			if (ft_print_msg(philo, FORK) == 1)
				return (false);
			pthread_mutex_unlock(&philo->his_fork.fork);
			pthread_mutex_unlock(&philo->nbr_fork->fork);
			return (true);
			}
		pthread_mutex_unlock(&philo->his_fork.fork);
		pthread_mutex_unlock(&philo->nbr_fork->fork);
		usleep(500);
	}
	return (false);
} */

bool	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_forks_lock);
	if (philo->his_fork.idx == -1 && philo->nbr_fork->idx == -1)
	{
		pthread_mutex_lock(&philo->his_fork.fork);
		pthread_mutex_lock(&philo->nbr_fork->fork);
		philo->his_fork.idx = philo->idx;
		ft_print_msg(philo, FORK);
		philo->nbr_fork->idx = philo->idx;
		ft_print_msg(philo, FORK);
		pthread_mutex_unlock(philo->mutex_forks_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->mutex_forks_lock);
	return (false);
}


void	*ft_routine_philos(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex_start);
	pthread_mutex_unlock(philo->mutex_start);
	if (DEBUG)
		printf("philo[%d] created\n", philo->idx);
	philo->last_meal = philo->ms_die;
	if (!(philo->idx & 1))
		ft_usleep(philo->ms_eat / 2);
	while (philo->nb_meals == -1 || philo->meals < philo->nb_meals)
	{
		if (ft_think(philo) == false)
			break ;
/* 		if (ft_take_forks(philo) == false)
			break ; */
		if (ft_eat(philo) == false)
			break ;
/* 		if (philo->nb_meals != 1)
			philo->meals += 1; */
		if (ft_sleep(philo) == false)
			break ;
/* 		if (ft_think(philo) == false)
			break ; */
		usleep(500);
	}
	return (arg);
}
