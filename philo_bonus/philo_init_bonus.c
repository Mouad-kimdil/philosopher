#include "philo_bonus.h"

t_philo	*init_philo(t_arg *args, t_sema *sem)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = malloc(sizeof(t_philo) * args->num_of_philos);
	while (i < args->num_of_philos)
	{
		ph[i].philo_id = i + 1;
		ph[i].eating = false;
		ph[i].meals = 0;
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].dead = &args->die;
		ph[i].eated = &args->eated;
		ph[i].args = args;
		ph[i].pid = -1;
		ph[i].eated_lock = sem->eated;
		ph[i].dead_lock = sem->dead;
		ph[i].message_lock = sem->message;
		ph[i].meal_lock = sem->meal;
		ph[i].forks = sem->forks;
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
	args->die = 0;
	args->eated = 0;
	args->status = -1;
}
