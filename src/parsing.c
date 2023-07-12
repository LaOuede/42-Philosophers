/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/12 13:52:57 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	args_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[++i])
		if (ft_atoi(argv[i]) < 60)
			return (false);
	return (true);
}

bool	nb_philo_check(char *str)
{
	if ((ft_atoi(str) <= 0) || (ft_atoi(str) > 200))
		return (false);
	return (true);
}

bool	digit_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!is_digit(argv[i]))
			return (false);
	return (true);
}

bool	parsing(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		if (digit_check(argv) == true)
			if (nb_philo_check(argv[1]) == true)
				if (args_check(argv) == true)
					return (true);
	return (false);
}
