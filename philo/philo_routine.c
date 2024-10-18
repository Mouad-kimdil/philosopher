/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:38:17 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/18 01:31:51 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *ph)
{
	print_message(ph, EAT);
	ft_usleep(ph->args->time_to_sleep);
}

void	think_routine(t_philo *ph)
{
	print_message(ph, THINK);
}

void	eat_routine(t_philo *ph)
{
	pthread_mutex_lock(ph->r_fork);
	print_message(ph, TAKE_FORK);
	if (ph->args->num_of_philos == 1)
	{
		ft_usleep(ph->args->time_to_die);
		pthread_mutex_unlock(ph->r_fork);
		return ;
	}
	pthread_mutex_lock(ph->l_fork);	
	print_message(ph, TAKE_FORK);
	ph->eating = true;
	print_message(ph, EAT);
	pthread_mutex_lock(ph->meal);
	ph->last_meal_time = get_current_time();
	ph->meals++;
	pthread_mutex_unlock(ph->meal);
	ft_usleep(ph->args->time_to_eat);
	ph->eating = false;
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->philo_id % 2 == 0)
		ft_usleep(1);
	while (!dead_l(ph))
	{
		eat_routine(ph);
		sleep_routine(ph);
		think_routine(ph);
	}
	return (arg);
}