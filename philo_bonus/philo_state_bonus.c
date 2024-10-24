#include "philo_bonus.h"

bool	dead_l(t_philo *ph)
{
	sem_wait(ph->dead_lock);
	sem_wait(ph->eated_lock);
	if (*ph->dead == 1 || *ph->eated == 1)
		return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), true);
	return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), false);
}

bool	check_is_eat(t_philo *ph)
{
	if (ph->args->num_of_philos == -1)
		return (false);
	sem_wait(ph->meal_lock);
	if (ph->meals == ph->args->num_of_philos)
	{
		sem_wait(ph->eated_lock);
		*ph->eated = 1;
		sem_post(ph->meal_lock);
		return (sem_post(ph->eated_lock), true);
	}
	sem_post(ph->eated_lock);
	return (sem_post(ph->meal_lock), false);
}

bool	philo_dead(t_philo *ph, size_t time_to_die)
{
	size_t	time;

	time = get_current_time() - ph->last_meal_time;
	sem_wait(ph->meal_lock);
	if (time >= time_to_die && ph->eating == false)
		return (sem_post(ph->meal_lock), true);
	sem_post(ph->meal_lock);
	return (false);
}

bool	check_is_dead(t_philo *ph)
{
	if (philo_dead(ph, ph->args->time_to_die))
	{
		print_message(ph, DEAD);
		sem_wait(ph->dead_lock);
		*ph->dead = 1;
		sem_post(ph->dead_lock);
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
		ft_usleep(100);
	}
	return (arg);
}
