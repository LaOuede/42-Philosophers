/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/24 11:19:10 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	ft_clean_n_quit(t_waiter *waiter)
{
	pthread_mutex_destroy(&waiter->start);
	pthread_mutex_destroy(&waiter->eat);
	pthread_mutex_destroy(&waiter->dead);
	pthread_mutex_destroy(&waiter->print);
}
