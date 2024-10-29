/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:25:58 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/29 23:34:04 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *ph)
{
	print_message(ph, SLEEP);
	ft_usleep(ph->args->time_to_sleep);
}

void	think_routine(t_philo *ph)
{
	print_message(ph, THINK);
}

void	lock_forks(t_philo *ph, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(ph->l_fork);
		print_message(ph, TAKE_FORK);
		pthread_mutex_lock(ph->r_fork);
		print_message(ph, TAKE_FORK);
		return ;
	}
	pthread_mutex_lock(ph->r_fork);
	print_message(ph, TAKE_FORK);
	pthread_mutex_lock(ph->l_fork);
	print_message(ph, TAKE_FORK);
}

void	eat_routine(t_philo *ph)
{
	if (ph->args->num_of_philos == 1)
	{
		pthread_mutex_lock(ph->r_fork);
		print_message(ph, TAKE_FORK);
		ft_usleep(ph->args->time_to_die);
		pthread_mutex_unlock(ph->r_fork);
		return ;
	}
	if (ph->philo_id % 2 == 0)
		lock_forks(ph, 0);
	else
		lock_forks(ph, 1);
	pthread_mutex_lock(ph->meal);
	print_message(ph, EAT);
	ph->eating = true;
	ph->last_meal_time = time_now();
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
		usleep(10);
	while (!dead_l(ph))
	{
		eat_routine(ph);
		ft_usleep(2);
		sleep_routine(ph);
		think_routine(ph);
	}
	return (arg);
}
