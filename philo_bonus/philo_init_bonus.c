#include "philo_bonus.h"

t_philo	*init_philo(t_arg *args, t_sema *sem)
{
	t_philo	*ph;
	int		i;

	ph = malloc(sizeof(t_philo) * args->num_of_philos);
	if (!ph)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		ph[i].philo_id = i + 1;
		ph[i].eating = false;
		ph[i].meals = 0;
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].dead = &args->die;
		ph[i].sem = sem;
		ph[i].args = args;
		i++;
	}
	return (ph);
}

void	init_sem(t_sema *sem, t_arg *args)
{
	unlink("dead_lock");
	unlink("message_lock");
	unlink("meal_lock");
	unlink("forks");
	sem->dead_lock = sem_open("dead_lock", O_CREAT, 0644, 1);
	sem->message_lock = sem_open("message_lock", O_CREAT, 0644, 1);
	sem->meal_lock = sem_open("meal_lock", O_CREAT, 0644, 1);
	sem->forks = sem_open("forks", O_CREAT, 0644, args->num_of_philos);
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
	args->die = 0;
	printf("arg->die: %p\n", &args->die);
}
