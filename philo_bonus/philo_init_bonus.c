/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:09:27 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 04:41:41 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo_help(t_philo *ph, int i)
{
	ph[i].philo_id = i + 1;
	ph[i].start_time = time_now();
	ph[i].last_meal_time = time_now();
	ph[i].pid = -1;
	ph[i].i = 0;
}

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
		atomic_init(&ph[i].last_meal_time, time_now());
		init_philo_help(ph, i);
		ph[i].eated_lock = sem->eated;
		ph[i].message_lock = sem->message;
		ph[i].meal_lock = sem->meal;
		ph[i].dead_lock = sem->dead;
		ph[i].forks = sem->forks;
		ph[i].args = args;
		i++;
	}
	return (ph);
}

int	init_arg(t_arg *args, char **av)
{
	args->num_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->num_times_to_eat = -1;
	if (av[5])
		args->num_times_to_eat = ft_atoi(av[5]);
	if (args->num_of_philos > 200)
		return (1);
	return (0);
}
