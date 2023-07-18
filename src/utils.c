/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/18 15:01:14 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	char	*dest;

	len = size * count;
	dest = (void *)malloc(len);
	if (!dest)
		return (NULL);
	while (len-- > 0)
		dest[len] = 0;
	return (dest);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	if (!str)
		return (0);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg *= -1;
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
		res = res * 10 + (str[i++] - 48);
	res *= neg;
	if (res > INT_MAX || res < INT_MIN)
		return (0);
	return (res * neg);
}

bool	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			continue ;
		else
			return (false);
	}
	return (true);
}

int	timestamp_in_ms(void)
{
	time_t			time;
	t_waiter		*waiter;
	struct timeval	time_now;

	printf(KYEL "---------- "KGRN"START_TIME"KYEL" ----------\n" RT);
	waiter = init_waiter();
	gettimeofday(&time_now, NULL);
	time = ((time_now.tv_sec - waiter->start_time->tv_sec) * 1000 + \
		(time_now.tv_usec - waiter->start_time->tv_usec) / 1000);
	printf("start_time = %ld\n", ((waiter->start_time->tv_sec) * 1000 + (waiter->start_time->tv_usec) / 1000));
	printf("time_now = %ld\n", (time_now.tv_sec * 1000 + time_now.tv_usec / 1000));
	printf("dif_time = %ld ms\n", time);
	return (time);
}
