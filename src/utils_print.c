/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:25:04 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/20 15:25:16 by gle-roux         ###   ########.fr       */
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

int	ft_print_msg(t_waiter *waiter, int idx, char *msg)
{
	time_t	timestamp;

	pthread_mutex_lock(&waiter->print);
	if (ft_night_watch(waiter, idx) == true)
	{
		timestamp = ft_timestamp_in_ms(waiter);
		printf("%ld %d %s\n", timestamp, idx, msg);
		pthread_mutex_unlock(&waiter->print);
		return (0);
	}
	printf("Someone has died!\n");
	pthread_mutex_unlock(&waiter->print);
	return (1);
}
