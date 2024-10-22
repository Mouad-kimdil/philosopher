#include "philo_bonus.h"

void	print_args(t_philo *ph, int i)
{
	printf("philo_id: %d\n-------------------------------------\n", i + 1);
	printf("Meals: %d\n", ph->meals);
    printf("philo ID: %d\n", ph->philo_id);
    printf("Eating: %s\n", ph->eating ? "true" : "false");
    printf("Start Time: %zu\n", ph->start_time);
    printf("Last Meal Time: %zu\n", ph->last_meal_time);
    printf("Address of dead (int *): %p\n", (void *)ph->dead);
    printf("Address of message_lock (sem_t *): %p\n", (void *)ph->sem->message_lock);
    printf("Address of dead_lock (sem_t *): %p\n", (void *)ph->sem->dead_lock);
    printf("Address of meal_lock (sem_t *): %p\n", (void *)ph->sem->meal_lock);
    printf("Address of forks (sem_t *): %p\n", (void *)ph->sem->forks);
    printf("Address of args (t_arg *): %p\n", (void *)ph->args);
	printf("Number of Philosophers: %d\n", ph->args->num_of_philos);
    printf("Time to Die: %zu\n", ph->args->time_to_die);
    printf("Time to Eat: %zu\n", ph->args->time_to_eat);
    printf("Time to Sleep: %zu\n", ph->args->time_to_sleep);
    printf("Number of Times to Eat: %d\n", ph->args->num_times_to_eat);
	printf("-------------------------------------\n");
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
}