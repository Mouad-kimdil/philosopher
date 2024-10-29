/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:14:49 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 00:15:02 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	dead_l(t_philo *ph)
{
	sem_wait(ph->eated_lock);
	sem_wait(ph->dead_lock);
	if (atomic_load(&ph->dead) == 1 || atomic_load(&ph->eated) == 1)
		return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), true);
	return (sem_post(ph->eated_lock), sem_post(ph->dead_lock), false);
}

bool	check_is_eat(t_philo *ph)
{
	if (ph->args->num_times_to_eat == -1)
		return (false);
	sem_wait(ph->meal_lock);
	if (atomic_load(&ph->meals) == ph->args->num_times_to_eat)
	{
		sem_wait(ph->eated_lock);
		atomic_store(&ph->eated, 1);
		sem_post(ph->eated_lock);
		sem_post(ph->meal_lock);
		return (true);
	}
	sem_post(ph->meal_lock);
	return (false);
}

bool	philo_dead(t_philo *ph, size_t time_to_die)
{
	sem_wait(ph->meal_lock);
	if (time_now() - ph->last_meal_time >= time_to_die
		&& atomic_load(&ph->eating) == false)
	{
		sem_post(ph->meal_lock);
		return (true);
	}
	sem_post(ph->meal_lock);
	return (false);
}

bool	check_is_dead(t_philo *ph)
{
	if (philo_dead(ph, ph->args->time_to_die))
	{
		sem_wait(ph->dead_lock);
		atomic_store(&ph->dead, 1);
		sem_post(ph->dead_lock);
		exit (ph->i);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *) arg;
	while (true)
	{
		if (check_is_eat(ph) || check_is_dead(ph))
			break ;
	}
	return (arg);
}
