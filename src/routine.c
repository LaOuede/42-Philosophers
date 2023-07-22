/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/22 14:34:59 by gwenolalero      ###   ########.fr       */
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
	if (ft_check_meals(waiter, idx) == true)
	{
		if (ft_print_msg(waiter, idx, EAT))
		{
			printf("Philo[%d] died eating!\n", idx);
			return (false);
		}
		//printf("waiter->sated = %d\n", waiter->sated);
		waiter->philo[idx].last_meal = ft_timestamp_in_ms(waiter);
		//printf("last_meal = %ld\n", waiter->philo[idx].last_meal);
		if (ft_eat_monitoring(waiter, waiter->param->ms_eat, idx) == true)
		{
			//ft_usleep(waiter->param->ms_eat);
			waiter->philo[idx].his_fork.idx = -1;
			waiter->philo[idx].nbr_fork->idx = -1;
			pthread_mutex_unlock(&waiter->philo[idx].his_fork.fork);
			pthread_mutex_unlock(&waiter->philo[idx].nbr_fork->fork);
			usleep(500);
			return (true);
		}
	}
	return (false);
}

bool	ft_take_forks(t_waiter *waiter, int idx)
{
	t_philo	*philo;

	philo = ft_init_philo(0);
	while (42)
	{
		pthread_mutex_lock(&philo[idx].his_fork.fork);
		pthread_mutex_lock(&philo[idx].nbr_fork->fork);
		if (philo[idx].his_fork.idx == -1 \
			&& philo[idx].nbr_fork->idx == -1)
		{
			if (ft_print_msg(waiter, idx, FORK) == 1)
			{
				printf("Philo[%d] died forking!\n", idx);
				return (false);
			}
			philo[idx].his_fork.idx = idx;
			if (ft_print_msg(waiter, idx, FORK) == 1)
			{
				printf("Philo[%d] died forking!\n", idx);
				return (false);
			}
			philo[idx].nbr_fork->idx = idx;
			return (true);
		}
	}
	pthread_mutex_unlock(&philo[idx].his_fork.fork);
	pthread_mutex_unlock(&philo[idx].nbr_fork->fork);
	return (true);
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
/* 		if (ft_take_forks(waiter, idx) == false)
			break ;
		if (ft_eat(waiter, idx) == false)
			break ;
		if (ft_sleep(waiter, idx) == false)
			break ;
		if (ft_think(waiter, idx) == false)
			break; */
		if (ft_take_forks(waiter, idx) == true)
			if (ft_eat(waiter, idx) == true)
				if (ft_sleep(waiter, idx) == true)
					if (ft_think(waiter, idx) == false)
						break;
	}
	return (NULL);
}
