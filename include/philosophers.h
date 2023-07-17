/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:10:07 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/17 16:19:12 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
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

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			free;
	bool			waiting;
	bool			taken;
}t_fork;

typedef struct s_philo
{
	int			idx;
	pthread_t	thread;
	bool		eating;
	bool		thinking;
	bool		sleeping;
	bool		dead;
	int			meals;
}t_philo;

typedef struct s_param
{
	int	nb_philo;
	int	ms_die;
	int	ms_eat;
	int	ms_sleep;
	int	nb_meals;
}t_param;

typedef struct s_waiter
{
	struct timeval	*start_time;
	t_param			*param;
	t_philo			*philo;
	pthread_mutex_t	start;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	bool			all_alive;
	bool			sated;

}t_waiter;

/* ------------------- ROUTINE -------------------- */
int			diner(t_waiter *waiter);
void		*routine_philos(void *arg);
void		*routine_philo_alone(void *arg);
int			the_one_and_only(t_waiter *waiter);

/* -------------PARSING & INITIALIZING------------- */
bool		create_threads(t_waiter *waiter);
t_waiter	*init_waiter(void);
t_param		*init_param(int argc, char **argv);
t_philo		*init_philo(t_waiter *ms);
bool		parsing(int argc, char **argv);

/* ------------------CLEANING UP------------------- */
void		clean_n_quit(t_waiter *ms);
void		*free_null(void *ptr);

/* ---------------------UTILS---------------------- */
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
bool		is_digit(char *str);
void		putstr_fd(char const *s, int fd);

/* ---------------------DEBUG---------------------- */
int			print_time(void);

#endif
