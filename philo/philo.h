/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:26:11 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 03:20:02 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_mutex
{
	int				death;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*mel;
}	t_mutex;

typedef struct s_arg
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
}	t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	bool			eating;
	int				meals;
	int				*dead;
	pthread_mutex_t	*end_lock;
	pthread_mutex_t	*message;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	size_t			start_time;
	size_t			last_meal_time;
	t_arg			*args;
}	t_philo;

# define TAKE_FORK "has taken a fork"
# define DROP_FORK "has dropped a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "is dead"

void			ft_putchar(char c, int fd);
void			ft_putstr(char *s, int fd);
int				is_number(int c);
int				is_valid_number(char *str);
int				check_input(char **av);
int				ft_strlen(char *str);
long			ft_atoi(char *str);
int				ft_usleep(size_t milliseconds);
size_t			time_now(void);
void			sleep_routine(t_philo *ph);
void			think_routine(t_philo *ph);
void			eat_routine(t_philo *ph);
void			*routine(void *arg);
void			free_forks(pthread_mutex_t *forks, int i);
pthread_mutex_t	*mutex_fork(t_arg *args);
pthread_mutex_t	*mutex_end(void);
pthread_mutex_t	*mutex_message(void);
pthread_mutex_t	*mutex_meal(void);
bool			philo_dead(t_philo *ph, size_t time_to_die);
bool			check_is_dead(t_philo *ph);
bool			check_is_eat(t_philo *ph);
int				check_overflow(char *str);
int				init_arg(t_arg *arg, char **av);
t_philo			*init_ph(t_arg *args, pthread_mutex_t *forks, t_mutex *mutex);
void			*detach(void *arg);
bool			dead_l(t_philo *ph);
void			print_message(t_philo *ph, char *message);
int				start_philo(t_arg *args, t_philo *ph);
void			lock_forks(t_philo *ph, int flag);
void			my_free(void **arg);
void			free_locks(t_mutex *mutex, pthread_mutex_t *forks, int num);
#endif