#include "philo_bonus.h"

void	print_message(t_philo *ph, char *s)
{
	size_t	time;

	sem_wait(ph->sem->message_lock);
	time = get_current_time() - ph->start_time;
	if (!dead_l(ph))		
		printf("%zu %d %s\n", time, ph->philo_id, s);
	sem_post(ph->sem->message_lock);
}

void	eat_routine(t_philo *ph)
{
	sem_wait(ph->sem->meal_lock);
	if (ph->args->num_of_philos == 1)
	{
		sem_wait(ph->sem->forks);
		print_message(ph, TAKE_FORK);
		ft_usleep(ph->args->time_to_eat);
		sem_post(ph->sem->forks);
		sem_post(ph->sem->meal_lock);
		return ;
	}
	sem_wait(ph->sem->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->sem->forks);
	print_message(ph, TAKE_FORK);
	ph->eating = true;
	print_message(ph, EAT);
	ph->last_meal_time = get_current_time();
	ph->meals++;
	sem_post(ph->sem->meal_lock);
	ft_usleep(ph->args->time_to_sleep);
	ph->eating = false;
	sem_post(ph->sem->forks);
	sem_post(ph->sem->forks);
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
	while (!dead_l(ph))
	{
		eat_routine(ph);
		think_routine(ph);
		sleep_routine(ph);
	}
}

void	child(t_philo *ph)
{
	ph->pid = fork();
	if (ph->pid == -1)
		return ;
	if (ph->pid == 0)
		philo_routine(ph);
}

void	start_philo(t_philo *ph)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		monitoring(ph);
	else
	{
		while (i < ph->args->num_of_philos)
		{
			child(ph);
			i++;
		}
		waitpid(pid, NULL, 0);
		while (wait(NULL) != -1)
			;
	}
	
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
	init_sem(&sem, &args);
	ph = init_philo(&args, &sem);
	start_philo(ph);
}