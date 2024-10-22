#include "philo_bonus.h"

bool	dead_l(t_philo *ph)
{
	sem_wait(ph->sem->dead_lock);
	if (*ph->dead == 1)
		return (sem_post(ph->sem->dead_lock), true);
	return (sem_post(ph->sem->dead_lock), false);
}

bool	check_is_eat(t_philo *ph)
{
	int	i;
	int	finish;

	i = -1;
	sem_wait(ph[0].sem->dead_lock);
	if (ph[0].args->num_of_philos == -1)
		return (sem_post(ph[0].sem->dead_lock), false);
	sem_wait(ph[0].sem->dead_lock);
	finish = 0;
	while (++i < ph[0].args->num_of_philos)
	{
		sem_wait(ph[i].sem->meal_lock);
		if (ph[i].meals >= ph[0].args->num_of_philos)
			finish++;
		sem_post(ph[i].sem->meal_lock);
	}
	if (finish == ph[0].args->num_of_philos)
	{
		sem_wait(ph[0].sem->dead_lock);
		*ph->dead = 1;
		return (sem_post(ph[0].sem->dead_lock), true);
	}
	return (false);
}

bool	philo_dead(t_philo *ph)
{
	sem_wait(ph->sem->meal_lock);
	if (get_current_time() - ph->last_meal_time >= ph->args->time_to_die
		&& ph->eating == false)
			return (sem_post(ph->sem->meal_lock), true);
	sem_post(ph->sem->meal_lock);
	return (false);
}

bool	check_is_dead(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph[0].args->num_of_philos)
	{
		if (philo_dead(&ph[i]))
		{
			print_message(ph, DEAD);
			sem_wait(ph[i].sem->dead_lock);
			*ph->dead = 1;
			sem_post(ph[i].sem->dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

void	monitoring(t_philo *ph)
{
	while (true)
	{
		if (check_is_eat(ph) || check_is_dead(ph))
			break ;
		ft_usleep(200);
	}
}
