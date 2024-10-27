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
	sem_post(ph->meal_lock);
	ft_usleep(ph->args->time_to_eat);
	atomic_store(&ph->eating, 0);
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
	if (atomic_load(&ph->eated) == 1)
		exit (212);
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
		ph[i].i = i;
		pids[i] = child(&ph[i]);
		i++;
	}
	meal = 0;
	int flag = 1;
	while (flag)
	{
		i = 0;
		while (i < ph->args->num_of_philos)
		{
			waitpid(pids[i], &status, WNOHANG);
			if (WEXITSTATUS(status) == i)
			{
				printf("%zu %d %s\n", get_current_time() - ph->start_time, i + 1, DEAD);
				flag = 0;
				break ;
			}
			if (WEXITSTATUS(status) == 212)
			{
				meal++;
				status = -1;
			}
			if (meal == ph->args->num_of_philos)
			{
				flag = 0;
				break ;
			}
			i++;
		}
		usleep(300);
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
}