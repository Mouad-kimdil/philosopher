/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:32:11 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/29 23:34:04 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_routine(t_philo *ph)
{
	if (ph->args->num_of_philos == 1)
	{
		sem_wait(ph->forks);
		print_message(ph, TAKE_FORK);
		ft_usleep(ph->args->time_to_die);
		sem_post(ph->forks);
		return ;
	}
	if (dead_l(ph))
		return ;
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->forks);
	print_message(ph, TAKE_FORK);
	sem_wait(ph->meal_lock);
	atomic_store(&ph->eating, 1);
	print_message(ph, EAT);
	atomic_store(&ph->last_meal_time, time_now());
	atomic_fetch_add(&ph->meals, 1);
	sem_post(ph->meal_lock);
	ft_usleep(ph->args->time_to_eat);
	atomic_store(&ph->eating, 0);
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	think_routine(t_philo *ph)
{
	print_message(ph, THINK);
}

void	sleep_routine(t_philo *ph)
{
	print_message(ph, SLEEP);
	ft_usleep(ph->args->time_to_sleep);
}

void	philo_routine(t_philo *ph)
{
	pthread_t	thread_1;

	if (pthread_create(&thread_1, NULL, monitoring, ph) != 0)
		return ;
	while (!dead_l(ph))
	{
		eat_routine(ph);
		if (dead_l(ph))
			break ;
		think_routine(ph);
		sleep_routine(ph);
	}
	if (pthread_join(thread_1, NULL) != 0)
		return ;
	if (atomic_load(&ph->eated) == 1)
		exit (212);
}
