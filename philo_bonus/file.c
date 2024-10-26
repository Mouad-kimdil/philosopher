#include "philo_bonus.h"

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((sign * result));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_number(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i], fd);
		i++;
	}
}
#include "philo_bonus.h"

void	print_message(t_philo *ph, char *s)
{
	sem_wait(ph->message_lock);	
	printf("%zu %d %s\n", get_current_time() - ph->start_time, ph->philo_id, s);
	sem_post(ph->message_lock);
}

void	eat_routine(t_philo *ph)
{
	if (ph->args->num_of_philos == 1)
	{
		sem_wait(ph->forks);
		print_message(ph, TAKE_FORK);
		ft_usleep(ph->args->time_to_die);
		sem_post(ph->forks);
		return ;
	}
	if (dead_l(ph))
        return ;
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->meal_lock);
    atomic_store(&ph->eating, 1);
    print_message(ph, EAT);
    atomic_store(&ph->last_meal_time, get_current_time());
    atomic_fetch_add(&ph->meals, 1);
    atomic_store(&ph->eating, 0);
    ft_usleep(ph->args->time_to_eat);
    sem_post(ph->meal_lock);
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	think_routine(t_philo *ph)
{
	print_message(ph, THINK);
}

void	sleep_routine(t_philo *ph)
{
	print_message(ph, SLEEP);
	ft_usleep(ph->args->time_to_sleep);
}

void	philo_routine(t_philo *ph)
{
	pthread_t	thread_1;

	if (pthread_create(&thread_1, NULL, monitoring, ph) != 0)
		return ;
	while (!dead_l(ph))
    {
        eat_routine(ph);
        if (dead_l(ph))
            break ;
        think_routine(ph);
        sleep_routine(ph);
    }
	if (pthread_join(thread_1, NULL) != 0)
		return ;
	sem_wait(ph->meal_lock);
	if (atomic_load(&ph->eated) == 1)
	{
		sem_post(ph->meal_lock);
		exit(2);
	}
	sem_post(ph->meal_lock);
	sem_wait(ph->dead_lock);
	if (atomic_load(&ph->dead) == 1)
	{
		sem_post(ph->dead_lock);
		exit (1);
	}
	sem_post(ph->dead_lock);
}

int	child(t_philo *ph)
{
	ph->pid = fork();
	if (ph->pid == -1)
		return (0);
	if (ph->pid == 0)
		philo_routine(ph);
	return (ph->pid);
}

int	start_philo(t_philo *ph)
{
	int			*pids;
	int			status;
	int			i;
	int			meal;

	pids = malloc(sizeof(int) * ph->args->num_of_philos);
	if (!pids)
		return (1);
	i = 0;
	while (i < ph->args->num_of_philos)
	{
		pids[i] = child(&ph[i]);
		i++;
	}
	meal = 0;
	while (1)
    {
        int exited_pid = waitpid(-1, &status, WNOHANG);
        if (exited_pid > 0)
        {
            if (WEXITSTATUS(status) == 1)
                break ;
            if (WEXITSTATUS(status) == 2)
                meal++;
            if (meal == ph->args->num_of_philos)
                break ;
        }
        usleep(100);
    }
	i = 0;
	while (i < ph->args->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	return (0);
}

sem_t	*init_semaphores(char *s, int value)
{
	sem_t	*semaphore;

	sem_unlink(s);
	semaphore = sem_open(s, O_CREAT | O_EXCL, 0644, value);
	return (semaphore);
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*ph;
	t_sema	sem;

	if (ac != 5 && ac != 6)
		return (ft_putstr("invalid number of arguments\n", 2), 1);
	if (check_input(av))
		return (1);
	init_arg(&args, av);
	sem.message = init_semaphores("message", 1);
	sem.meal = init_semaphores("meal", 1);
	sem.eated = init_semaphores("eated", 1);
	sem.dead = init_semaphores("dead", 1);
	sem.forks = init_semaphores("forks", args.num_of_philos);
	ph = init_philo(&args, &sem);
	start_philo(ph);
}#include "philo_bonus.h"

t_philo	*init_philo(t_arg *args, t_sema *sem)
{
    t_philo	*ph;
    int		i;

    i = 0;
    ph = malloc(sizeof(t_philo) * args->num_of_philos);
    if (!ph)
		return (NULL);
    while (i < args->num_of_philos)
    {
		atomic_init(&ph[i].eating, 0);
		atomic_init(&ph[i].meals, 0);
		atomic_init(&ph[i].eated, 0);
		atomic_init(&ph[i].dead, 0);
		atomic_init(&ph[i].last_meal_time, get_current_time());
		ph[i].philo_id = i + 1;
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].pid = -1;
		ph[i].eated_lock = sem->eated;
		ph[i].message_lock = sem->message;
		ph[i].meal_lock = sem->meal;
		ph[i].dead_lock = sem->dead;
		ph[i].forks = sem->forks;
		ph[i].args = args;
		i++;
    }
    return (ph);
}

void	init_arg(t_arg *args, char **av)
{
	args->num_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->num_times_to_eat = -1;
	if (av[5])
		args->num_times_to_eat = ft_atoi(av[5]);
}
#include "philo_bonus.h"

bool	dead_l(t_philo *ph)
{
	sem_wait(ph->eated_lock);
	sem_wait(ph->dead_lock);
	if (atomic_load(&ph->dead) == 1 || atomic_load(&ph->eated) == 1)
		return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), true);
	return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), false);
}

bool	check_is_eat(t_philo *ph)
{
	if (ph->args->num_times_to_eat == -1)
		return (false);
	sem_wait(ph->meal_lock);
	if (atomic_load(&ph->meals) == ph->args->num_times_to_eat)
	{
		sem_wait(ph->eated_lock);
		atomic_store(&ph->eated, 1);
		sem_post(ph->eated_lock);
		sem_post(ph->meal_lock);
		return (true);
	}
	sem_post(ph->meal_lock);
	return (false);
}

bool	philo_dead(t_philo *ph, size_t time_to_die)
{
	sem_wait(ph->meal_lock);
	if (get_current_time() - ph->last_meal_time >= time_to_die
		&& atomic_load(&ph->eating) == false)
	{
		sem_post(ph->meal_lock);
		return (true);
	}
	sem_post(ph->meal_lock);
	return (false);
}

bool	check_is_dead(t_philo *ph)
{
	if (philo_dead(ph, ph->args->time_to_die))
	{
		sem_wait(ph->dead_lock);
		atomic_store(&ph->dead, 1);
		sem_post(ph->dead_lock);
		print_message(ph, DEAD);
		return (true);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	t_philo *ph;

	ph = (t_philo *) arg;
	while (true)
	{
		if (check_is_eat(ph) || check_is_dead(ph))
			break ;
	}
	return (arg);
}
#include "philo_bonus.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(590);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
#include "philo_bonus.h"

int	is_valid_number(char *str)
{
	int	i;

	if (str && !str[0])
		return (ft_putstr("input must be a number", 1), 1);
	i = -1;
	while (str[++i])
	{
		if (!is_number(str[i]))
			return (ft_putstr("input must be a number", 2), 1);
	}
	return (0);
}

int	check_overflow(char *str)
{
	int		i;
	long	nb;
	int		len;

	i = 0;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len > 10)
		return (ft_putstr("number is too big", 2), 1);
	nb = ft_atoi(str);
	if (nb > INT_MAX)
		return (ft_putstr("number is too big", 2), 1);
	if (nb <= 0)
		return (ft_putstr("number must be positive", 2), 1);
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (is_valid_number(av[i]) || check_overflow(av[i]))
			return (1);
	}
	return (0);
}
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

typedef	struct s_sema
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
	atomic_size_t   last_meal_time;
	int				philo_id;
	size_t			start_time;
	sem_t			*dead_lock;
	sem_t			*eated_lock;
	sem_t			*message_lock;
	sem_t			*meal_lock;
	sem_t			*forks;
	t_arg			*args;
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
void	*monitoring(void *arg);
bool	check_is_dead(t_philo *ph);
bool	philo_dead(t_philo *ph, size_t time_to_die);
bool	check_is_eat(t_philo *ph);
bool	dead_l(t_philo *ph);
void	print_message(t_philo *ph, char *s);

#endif