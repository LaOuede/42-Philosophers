/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:10:07 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/25 16:42:57 by gwenolalero      ###   ########.fr       */
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
# define CREA	"created"

/* -------------------STRUCTURES------------------- */
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				idx;
}t_fork;

typedef struct s_philo
{
	int					idx;
	int					nb_philo;
	time_t				ms_die;
	time_t				ms_eat;
	time_t				ms_sleep;
	int					nb_meals;
	bool				am_i_dead;
	time_t				*start_time;
	t_fork				his_fork;
	t_fork				*nbr_fork;
	int					meals;
	time_t				last_meal;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	pthread_mutex_t		*mutex_start;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_forks_lock;
}t_philo;

typedef struct s_waiter
{
	int				nb_philo;
	time_t			ms_die;
	time_t			ms_eat;
	time_t			ms_sleep;
	int				nb_meals;
	int				*philo;
	time_t			start_time;
	pthread_mutex_t	start;
	pthread_mutex_t	print;
	pthread_mutex_t	forks_lock;
	bool			all_alive;
}t_waiter;

/* ---------------- INITIALIZATION ---------------- */
bool		ft_create_threads(t_waiter *waiter, \
	t_philo *philo, pthread_t *thread);
void		*ft_get_waiter(void *ptr);
void		ft_init_forks(t_philo *philo);
void		ft_init_philo(t_waiter *waiter, t_philo *philo);
void		ft_init_waiter(t_waiter *waiter, int argc, char **argv);

/* ------------------- PARSING -------------------- */
bool		ft_args_check(int argc, char **argv);
bool		ft_digit_check(char **argv);
bool		ft_nb_philo_check(char *str);
bool		ft_parsing(int argc, char **argv);

/* ------------------- ROUTINE -------------------- */
void		ft_dispose_forks(t_philo *philo);
int			ft_diner(t_waiter *waiter, t_philo *philo);
bool		ft_eat(t_philo *philo);
bool		ft_join_threads(t_philo *philo, pthread_t *thread);
bool		ft_monitoring(t_philo *philo, time_t limit);
void		*ft_routine_philos(void *arg);
void		*ft_routine_philo_alone(void *arg);
bool		ft_sleep(t_philo *philo);
int			ft_the_one_and_only(t_philo *philo, pthread_t *thread);
bool		ft_take_forks(t_philo *philo);
bool		ft_think(t_philo *philo);
bool		ft_think_n_fork_monitoring(t_philo *philo);

/* -------------------- UTILS --------------------- */
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_destroy_mutex(t_waiter *waiter);
void		*ft_free_null(void *ptr);
bool		ft_is_digit(char *str);

/* ------------------UTILS PRINT------------------- */
int			ft_print_msg(t_philo *philo, char *msg);
int			ft_print_msg_forks(t_philo *philo, char *msg);
void		ft_putstr_fd(char *s, int fd);

/* ------------------ UTILS TIME ------------------ */
time_t		ft_get_time(void);
time_t		ft_timestamp_in_ms(t_philo *philo);
void		ft_usleep(time_t time);

#endif
