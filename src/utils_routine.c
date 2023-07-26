/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 11:25:33 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_destroy_mutex(t_waiter *waiter, t_philo *philo)
{
	pthread_mutex_destroy(&waiter->start);
	pthread_mutex_destroy(&waiter->print);
	pthread_mutex_destroy(&waiter->forks_lock);
	pthread_mutex_destroy(&philo->his_fork.fork);
}

bool	ft_kill_threads(pthread_t *thread, int i)
{
	while (i-- >= 0)
	{
		if (pthread_join(thread[i], NULL))
			return (false);
	}
	return (true);
}

bool	ft_join_threads(t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		if (pthread_join(thread[i], NULL))
			return (false);
	}
	return (true);
}

void	ft_dispose_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->his_fork.fork);
	pthread_mutex_lock(&philo->nbr_fork->fork);
	philo->his_fork.idx = -1;
	philo->nbr_fork->idx = -1;
	pthread_mutex_unlock(&philo->his_fork.fork);
	pthread_mutex_unlock(&philo->nbr_fork->fork);
}
