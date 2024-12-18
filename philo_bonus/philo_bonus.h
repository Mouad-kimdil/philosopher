/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:08:21 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 05:06:41 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdatomic.h> 

typedef struct s_arg
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
}	t_arg;

typedef struct s_sema
{
	sem_t	*message;
	sem_t	*meal;
	sem_t	*eated;
	sem_t	*dead;
	sem_t	*forks;
}	t_sema;

typedef struct s_philo
{
	pid_t			pid;
	atomic_int		eated;
	atomic_int		meals;
	atomic_int		eating;
	atomic_int		dead;
	atomic_size_t	last_meal_time;
	int				philo_id;
	size_t			start_time;
	sem_t			*dead_lock;
	sem_t			*eated_lock;
	sem_t			*message_lock;
	sem_t			*meal_lock;
	sem_t			*forks;
	t_arg			*args;
	int				i;
}	t_philo;

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "is dead"

int		check_input(char **av);
int		check_overflow(char *str);
int		is_valid_number(char *str);
int		init_arg(t_arg *arg, char **av);
long	ft_atoi(char *str);
int		ft_strlen(char *str);
int		is_number(int c);
void	ft_putchar(char c, int fd);
void	ft_putstr(char *s, int fd);
int		ft_usleep(size_t milliseconds);
size_t	time_now(void);
t_philo	*init_philo(t_arg *args, t_sema *sem);
void	*monitoring(void *arg);
bool	check_is_dead(t_philo *ph);
bool	philo_dead(t_philo *ph, size_t time_to_die);
bool	check_is_eat(t_philo *ph);
bool	dead_l(t_philo *ph);
void	print_message(t_philo *ph, char *s);
void	eat_routine(t_philo *ph);
void	think_routine(t_philo *ph);
void	sleep_routine(t_philo *ph);
void	philo_routine(t_philo *ph);
int		child(t_philo *ph);
int		check_philos_status(int *pids, t_philo *ph);
int		start_philo(t_philo *ph);
sem_t	*init_semaphores(char *s, int value);
void	init_philo_help(t_philo *ph, int i);
void	close_sema(t_sema *sem);

#endif