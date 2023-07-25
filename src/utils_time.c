/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 15:07:25 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

time_t	ft_get_time(void)
{
	struct timeval	time;
	time_t			time_now;

	gettimeofday(&time, NULL);
	time_now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_now);
}

time_t	ft_timestamp_in_ms(t_philo *philo)
{
	time_t		time;
	time_t		time_now;

	time_now = ft_get_time();
	time = time_now - *philo->start_time;
	if (DEBUG)
	{
		printf(KYEL "---------- "KGRN"UTILS_TIME"KYEL" ----------\n" RT);
		printf("start_time = %ld\n", *philo->start_time);
		printf("time_now = %ld\n", time_now);
		printf("dif_time = %ld ms\n", time);
	}
	return (time);
}

void	ft_usleep(time_t time_sleep)
{
	time_t	time_now;

	time_now = ft_get_time();
	usleep((time_sleep - 10) * 1000);
	while (42)
	{
		if (ft_get_time() - time_now >= (time_sleep))
			break ;
		usleep(50);
	}
}

/* bool	ft_night_watch(t_philo *philo)
{
	t_waiter	*waiter;

	waiter = ft_get_waiter(NULL);
	while (42)
	{
		pthread_mutex_lock(philo->mutex_dead);
		if (waiter->all_alive == true)
		{
			usleep(500);
			pthread_mutex_unlock(philo->mutex_dead);
			return (true);
		}
		else
			break ;
	}
	pthread_mutex_unlock(philo->mutex_dead);
	return (false);
} */