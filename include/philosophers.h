/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:10:07 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/19 14:15:37 by gle-roux         ###   ########.fr       */
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
# define DEBUG 0
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

/* -----------------ERROR MESSAGE------------------ */
# define ERR_ARGS	"Usage : ./philo <nb_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> [nb_meals]\n"

/* ------------------MSG TO PRINT------------------ */
# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIED	"died"

/* -------------------STRUCTURES------------------- */
typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			free;
}t_fork;

typedef struct s_param
{
	int	nb_philo;
	int	ms_die;
	int	ms_eat;
	int	ms_sleep;
	int	nb_meals;
}t_param;

typedef struct s_philo
{
	int			idx;
	pthread_t	thread;
	bool		eating;
	t_fork		his_fork;
	t_fork		*nbr_fork;
	bool		thinking;
	bool		sleeping;
	bool		dead;
	int			meals;
	time_t		last_meal;
}t_philo;

typedef struct s_waiter
{
	time_t			start_time;
	t_param			*param;
	t_philo			*philo;
	pthread_mutex_t	start;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	bool			all_alive;
	bool			sated;

}t_waiter;

/* -------------PARSING & INITIALIZING------------- */
bool		ft_create_threads(t_waiter *waiter);
t_fork		ft_init_fork();
t_waiter	*ft_init_waiter(void);
t_param		*ft_init_param(int argc, char **argv);
t_philo		*ft_init_philo(t_waiter *waiter);
bool		ft_parsing(int argc, char **argv);

/* ------------------- ROUTINE -------------------- */
int			ft_diner(t_waiter *waiter);
void		*ft_routine_philos(void *arg);
void		*ft_routine_philo_alone(void *arg);
int			ft_the_one_and_only(t_waiter *waiter);
bool		ft_think_n_fork(t_waiter *waiter, int idx);

/* ---------------------UTILS---------------------- */
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
bool		ft_is_digit(char *str);

/* ------------------UTILS PRINT-------------------- */
void		ft_print_msg(t_waiter *waiter, int idx, char *msg);
void		ft_putstr_fd(char *s, int fd);

/* -------------------UTILS TIME-------------------- */
time_t		ft_get_time(void);
time_t		ft_timestamp_in_ms(t_waiter *waiter);
void		ft_usleep(time_t time);

/* ------------------CLEANING UP------------------- */
void		ft_clean_n_quit(t_waiter *ms);
void		*ft_free_null(void *ptr);

/* ---------------------DEBUG---------------------- */

#endif
