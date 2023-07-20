/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/20 15:41:22 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_eat(t_waiter *waiter, int idx)
{
	waiter->philo[idx].eating = true;
	ft_print_msg(waiter, idx, EAT);
	if (ft_check_meals(waiter, idx) == true)
	{
		ft_usleep(waiter->param->ms_eat);
		waiter->philo[idx].last_meal = ft_timestamp_in_ms(waiter);
		waiter->philo[idx].his_fork.taken = false;
		waiter->philo[idx].nbr_fork->taken = false;
		pthread_mutex_unlock(&waiter->philo[idx].his_fork.fork);
		pthread_mutex_unlock(&waiter->philo[idx].nbr_fork->fork);
		return (true);
	}
	return (false);
}

bool	ft_take_forks(t_waiter *waiter, int idx)
{
	t_philo	*philo;

	philo = ft_init_philo(0);
	ft_print_msg(waiter, idx, THINK);
	pthread_mutex_lock(&philo[idx].his_fork.fork);
	pthread_mutex_lock(&philo[idx].nbr_fork->fork);
	if (philo[idx].his_fork.taken == false && philo[idx].nbr_fork->taken == false)
	{
		philo[idx].his_fork.taken = true;
		ft_print_msg(waiter, idx, FORK);
		philo[idx].nbr_fork->taken = true;
		ft_print_msg(waiter, idx, FORK);
		return (true);
	}
	return (false);
}

void	*ft_routine_philos(void *arg)
{
	int			idx;
	t_waiter	*waiter;

	idx = *(int *)arg;
	waiter = ft_init_waiter();
	pthread_mutex_lock(&waiter->start);
	pthread_mutex_unlock(&waiter->start);
	ft_print_msg(waiter, idx, CREA);
	if (!(idx & 1))
		ft_usleep(waiter->param->ms_eat / 2);
	while (ft_still_standing(waiter, idx) == true && waiter->all_alive == true)
	{
		if (ft_take_forks(waiter, idx) == true)
		{
			if (ft_eat(waiter, idx) == false)
				break ;
			ft_print_msg(waiter, idx, SLEEP);
			ft_usleep(waiter->param->ms_sleep);
		}
	}
	return (0);
}
