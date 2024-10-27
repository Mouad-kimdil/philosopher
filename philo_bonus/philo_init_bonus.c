#include "philo_bonus.h"

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
		ph[i].i = 0;
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
