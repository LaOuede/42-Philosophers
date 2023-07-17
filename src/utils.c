/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/17 16:08:58 by gwenolalero      ###   ########.fr       */
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

void	putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	print_time(void)
{
	printf(KYEL "---------- "KGRN"START_TIME"KYEL" ----------\n" RT);
	struct timeval tv;
	time_t t;
	struct tm *info;
	char buffer[64];
 
	gettimeofday(&tv, NULL);
	t = tv.tv_sec;
	info = localtime(&t);
	printf("%s",asctime (info));
	strftime (buffer, sizeof buffer, "Today is %A, %B %d.\n", info);
	printf("%s",buffer);
	return 0;
}