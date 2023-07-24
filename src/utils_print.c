/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 16:24:47 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

int	ft_print_msg(t_philo *philo, int idx, char *msg)
{
	time_t	timestamp;

	pthread_mutex_lock(philo->mutex_print);
/* 	if (ft_still_standing(philo, idx) == true || waiter->all_alive == true)
	{ */
		timestamp = ft_timestamp_in_ms(philo);
		printf("%ld %d %s\n", timestamp, idx + 1, msg);
		pthread_mutex_unlock(philo->mutex_print);
		return (0);
/* 	}
	timestamp = ft_timestamp_in_ms(philo);
	printf("%ld %d %s\n", timestamp, idx + 1, DIED);
	pthread_mutex_unlock(philo->mutex_print);
	return (1); */
}
