/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:10:07 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/26 09:39:34 by gle-roux         ###   ########.fr       */
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

/* ---------------- ERROR MESSAGE ----------------- */
# define ERR_ARGS	"Usage : ./philo <nb_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> [nb_meals]\n"

/* ---------------- MSGs TO PRINT ----------------- */
# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIED	"died"
# define CREA	"created"

/* ------------------ STRUCTURES ------------------ */
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				idx;
}t_fork;

typedef struct s_philo
{
	int					idx;
	bool				am_i_dead;
	t_fork				his_fork;
	t_fork				*nbr_fork;
	int					meals;
	time_t				last_meal;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					nb_philo;
	time_t				ms_die;
	time_t				ms_eat;
	time_t				ms_sleep;
	int					nb_meals;
	time_t				*start_time;
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
	time_t			start_time;
	bool			all_alive;
	int				*philo;
	pthread_mutex_t	start;
	pthread_mutex_t	print;
	pthread_mutex_t	forks_lock;
}t_waiter;

/* ------------------- PARSING -------------------- */
bool		ft_args_check(int argc, char **argv);
bool		ft_digit_check(char **argv);
bool		ft_nb_philo_check(char *str);
bool		ft_parsing(int argc, char **argv);

/* ---------------- INITIALIZATION ---------------- */
void		ft_init_forks(t_philo *philo);
void		ft_init_philo(t_waiter *waiter, t_philo *philo);
void		ft_init_waiter(t_waiter *waiter, int argc, char **argv);

/* ------------------- ROUTINE -------------------- */
bool		ft_create_threads(t_waiter *waiter, \
t_philo *philo, pthread_t *thread);
void		ft_destroy_mutex(t_waiter *waiter, t_philo *philo);
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
void		*ft_get_waiter(void *ptr);
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
