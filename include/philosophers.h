/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:10:07 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/12 15:19:50 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/* ---------------------UTILS--------------------- */
# define DEBUG 1

/* ---------------------COLORS--------------------- */
# define KNRM "\x1B[m"
# define BLD "\x1B[1m"
# define KGRE "\x1B[2m"
# define KITA "\x1B[3m"
# define KUND "\x1B[4m"
# define KRST "\x1B[5m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"
# define RT   "\033[1;0m"

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_ARGS	"Usage : ./philo <nb_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> [nb_meals]\n"

/* -------------------STRUCTURES------------------- */
enum e_args_type
{
	NB_PHILO = 0,
	MS_DIE = 1,
	MS_EAT = 2,
	MS_SLEEP = 3,
	NB_MEALS = 4,
};

typedef struct s_param
{
	int	nb_philo;
	int	ms_die;
	int	ms_eat;
	int	ms_sleep;
	int	nb_meals;
}t_param;


/* -------------PARSING & INITIALIZING------------- */
void	init_param(t_param *param, int argc, char **argv);
bool	parsing(int argc, char **argv);

/* ------------------CLEANING UP------------------- */

/* ---------------------UTILS---------------------- */
int		ft_atoi(const char *str);
bool	is_digit(char *str);
void	putstr_fd(char const *s, int fd);

#endif
