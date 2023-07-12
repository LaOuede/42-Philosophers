/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/12 15:21:31 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_param	param;

	if ((argc == 5 || argc == 6) && parsing(argc, argv) == true)
	{
		init_param(&param, argc, argv);
		printf("Hello, world!");
	}
	else
		putstr_fd(ERR_ARGS, STDERR_FILENO);
	return (0);
}
