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

typedef struct s_arg
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	int				die;
}	t_arg;

typedef struct s_sema
{
	sem_t	*message_lock;
	sem_t	*dead_lock;
	sem_t	*meal_lock;
	sem_t	*forks;
}	t_sema;

typedef struct s_philo
{
	pid_t	pid;
	int		*dead;
	int		meals;
	int		philo_id;
	bool	eating;
	size_t	start_time;
	size_t	last_meal_time;
	t_sema	*sem;
	t_arg	*args;
}	t_philo;

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "is dead"

int		check_input(char **av);
int		check_overflow(char *str);
int		is_valid_number(char *str);
void	init_arg(t_arg *arg, char **av);
long	ft_atoi(char *str);
int		ft_strlen(char *str);
int		is_number(int c);
void	ft_putchar(char c, int fd);
void	ft_putstr(char *s, int fd);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
t_philo	*init_philo(t_arg *args, t_sema *sem);
void	init_sem(t_sema *sem, t_arg *args);
void	monitoring(t_philo *ph);
bool	check_is_dead(t_philo *ph);
bool	philo_dead(t_philo *ph);
bool	check_is_eat(t_philo *ph);
bool	dead_l(t_philo *ph);
void	print_message(t_philo *ph, char *s);

#endif