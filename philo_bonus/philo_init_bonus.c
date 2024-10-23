#include "philo_bonus.h"

void	init_philo(t_philo *ph, t_arg *args)
{
	int		i;

	sem_unlink("dead_lock");
	sem_unlink("message_lock");
	sem_unlink("meal_lock");
	sem_unlink("forks");
	ph->dead_lock = sem_open("dead_lock", O_CREAT, 0600, 1);
	ph->message_lock = sem_open("message_lock", O_CREAT, 0600, 1);
	ph->meal_lock = sem_open("meal_lock", O_CREAT, 0600, 1);
	ph->forks = sem_open("forks", O_CREAT, 0600, args->num_of_philos);
	i = 0;
	while (i < args->num_of_philos)
	{
		ph[i].philo_id = i + 1;
		ph[i].eating = false;
		ph[i].meals = 0;
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].dead = &args->die;
		ph[i].args = args;
		ph[i].pid = -1;
		i++;
	}
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
