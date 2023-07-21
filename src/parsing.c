/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/21 12:22:35 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	ft_args_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
		if (ft_atoi(argv[i]) < 60)
			return (false);
	return (true);
}

bool	ft_nb_philo_check(char *str)
{
	if ((ft_atoi(str) <= 0) || (ft_atoi(str) > 200))
		return (false);
	return (true);
}

bool	ft_digit_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_is_digit(argv[i]))
			return (false);
	return (true);
}

bool	ft_parsing(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		if (ft_digit_check(argv) == true)
			if (ft_nb_philo_check(argv[1]) == true)
				if (ft_args_check(argc, argv) == true)
					return (true);
	return (false);
}
