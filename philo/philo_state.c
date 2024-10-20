/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:44:13 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/20 18:18:39 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_dead(t_philo *ph, size_t time_to_die)
{
	pthread_mutex_lock(ph->meal);
	if (get_current_time() - ph->last_meal_time >= time_to_die
		&& ph->eating == false)
		return (pthread_mutex_unlock(ph->meal), true);
	pthread_mutex_unlock(ph->meal);
	return (false);
}

bool	check_is_dead(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph[0].args->num_of_philos)
	{
		if (philo_dead(&ph[i], ph[i].args->time_to_die))
		{
			print_message(ph, DEAD);
			pthread_mutex_lock(ph[i].end_lock);
			*ph->dead = 1;
			pthread_mutex_unlock(ph[i].end_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_is_eat(t_philo *ph)
{
	int	i;
	int	finish;

	i = -1;
	pthread_mutex_lock(ph[0].end_lock);
	if (ph[0].args->num_times_to_eat == -1)
		return (pthread_mutex_unlock(ph[0].end_lock), false);
	pthread_mutex_unlock(ph[0].end_lock);
	finish = 0;
	while (++i < ph[0].args->num_of_philos)
	{
		pthread_mutex_lock(ph[i].meal);
		if (ph[i].meals >= ph[i].args->num_times_to_eat)
			finish++;
		pthread_mutex_unlock(ph[i].meal);
	}
	if (finish == ph[0].args->num_of_philos)
	{
		pthread_mutex_lock(ph[0].end_lock);
		*ph->dead = 1;
		return (pthread_mutex_unlock(ph[0].end_lock), true);
	}
	return (false);
}

void	*deatach(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (true)
	{
		if (check_is_dead(ph) || check_is_eat(ph))
			break ;
		ft_usleep(200);
	}
	return (arg);
}
