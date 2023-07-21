/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 12:16:01 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_think(t_waiter *waiter, int idx)
{
	waiter->philo[idx].thinking = true;
	if (ft_print_msg(waiter, idx, THINK) == 1)
	{
		printf("Philo[%d] died thinking!\n", idx);
		return (false);
	}
	return (true);
}

bool	ft_sleep(t_waiter *waiter, int idx)
{
	waiter->philo[idx].sleeping = true;
	if (ft_print_msg(waiter, idx, SLEEP) == 1)
	{
		printf("Philo[%d] died sleeping!\n", idx);
		return (false);
	}
	ft_usleep(waiter->param->ms_sleep);
	return (true);
}

bool	ft_eat(t_waiter *waiter, int idx)
{
	waiter->philo[idx].eating = true;
	if (ft_print_msg(waiter, idx, EAT))
	{
		printf("Philo[%d] died eating!\n", idx);
		return (false);
	}
	if (ft_check_meals(waiter, idx) == true)
	{
		waiter->philo[idx].last_meal = ft_timestamp_in_ms(waiter);
		if (ft_smart_eat(waiter, idx) == true)
		{
			waiter->philo[idx].his_fork.taken = false;
			waiter->philo[idx].nbr_fork->taken = false;
			pthread_mutex_unlock(&waiter->philo[idx].his_fork.fork);
			pthread_mutex_unlock(&waiter->philo[idx].nbr_fork->fork);
			return (true);
		}
	}
	return (false);
}

bool	ft_think_n_forks(t_waiter *waiter, int idx)
{
	t_philo	*philo;

	philo = ft_init_philo(0);
/* 	if (ft_print_msg(waiter, idx, THINK) == 1)
	{
		printf("Philo[%d] died thinking!\n", idx);
		return (false);
	} */
	pthread_mutex_lock(&philo[idx].his_fork.fork);
	pthread_mutex_lock(&philo[idx].nbr_fork->fork);
	if (philo[idx].his_fork.taken == false \
		&& philo[idx].nbr_fork->taken == false)
	{
		if (ft_print_msg(waiter, idx, FORK) == 1)
		{
			printf("Philo[%d] died forking!\n", idx);
			return (false);
		}
		philo[idx].his_fork.taken = true;
		if (ft_print_msg(waiter, idx, FORK) == 1)
		{
			printf("Philo[%d] died forking!\n", idx);
			return (false);
		}
		philo[idx].nbr_fork->taken = true;
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
	//ft_print_msg(waiter, idx, CREA);
	if (!(idx & 1))
	{
		ft_print_msg(waiter, idx, THINK);
		ft_usleep(waiter->param->ms_eat / 2);
	}
	while (42)
	{
/* 		if (ft_think_n_forks(waiter, idx) == false)
			break ;
		if (ft_eat(waiter, idx) == false)
			break ;
		if (ft_sleep(waiter, idx) == false)
			break ;
		if (ft_think(waiter, idx) == false)
			break; */
		if (ft_think_n_forks(waiter, idx) == true)
			if (ft_eat(waiter, idx) == true)
				if (ft_sleep(waiter, idx) == true)
					if (ft_think(waiter, idx) == false)
						break;
	}
	return (0);
}
