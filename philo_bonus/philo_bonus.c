#include "philo_bonus.h"

void	print_message(t_philo *ph, char *s)
{
	size_t	time;

	sem_wait(ph->message_lock);
	time = get_current_time() - ph->start_time;
	if (!dead_l(ph))		
		printf("%zu %d %s\n", time, ph->philo_id, s);
	sem_post(ph->message_lock);
}

void	eat_routine(t_philo *ph)
{
	if (ph->args->num_of_philos == 1)
	{
		sem_wait(ph->forks);
		print_message(ph, TAKE_FORK);
		ft_usleep(ph->args->time_to_eat);
		sem_post(ph->forks);
		sem_post(ph->meal_lock);
		return ;
	}
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->meal_lock);
	ph->eating = true;
	print_message(ph, EAT);
	ph->last_meal_time = get_current_time();
	ph->meals++;
	sem_post(ph->meal_lock);
	ft_usleep(ph->args->time_to_sleep);
	ph->eating = false;
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
	while (!dead_l(ph))
	{
		eat_routine(ph);
		ft_usleep(9);
		think_routine(ph);
		sleep_routine(ph);
	}
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
	pid_t		*pids;
	pthread_t	thread;
	int			i;

	pids = malloc(sizeof(pid_t) * ph->args->num_of_philos);
	if (!pids)
		return (1);
	i = 0;
	if (pthread_create(&thread, NULL, monitoring, ph) != 0)
		return (1);
	while (i < ph->args->num_of_philos)
	{
		pids[i] = child(&ph[i]);
		i++;
	}
	if (pthread_join(thread, NULL) != 0)
		return (1);
	i = 0;
	while (i < ph->args->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}

sem_t	*init_dead(void)
{
	sem_t	*dead;

	sem_unlink("dead_lock");
	dead = sem_open("dead_lock", O_CREAT, 0644, 1);
	return (dead);
}

sem_t	*init_message(void)
{
	sem_t	*message;

	sem_unlink("message_lock");
	message = sem_open("message_lock", O_CREAT, 0644, 1);
	return (message);
}

sem_t	*init_meal(void)
{
	sem_t	*meal;

	sem_unlink("meal_lock");
	meal = sem_open("meal_lock", O_CREAT, 0644, 1);
	return (meal);
}

sem_t	*init_forks(int num_of_philos)
{
	sem_t	*forks;

	sem_unlink("forks_lock");
	forks = sem_open("forks_lock", O_CREAT, 0644, num_of_philos);
	return (forks);
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
	sem.dead = init_dead();
	sem.message = init_message();
	sem.meal = init_meal();
	sem.forks = init_forks(args.num_of_philos);
	ph = init_philo(&args, &sem);
	start_philo(ph);
}