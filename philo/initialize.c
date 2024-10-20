/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:46:59 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/20 18:06:08 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(pthread_mutex_t *fork, int num_of_philo)
{
	int	i;

	i = -1;
	while (++i < num_of_philo)
	{
		if (pthread_mutex_destroy(&fork[i]) != 0)
			return (1);
	}
	return (free(fork), fork = NULL, 0);
}

int	free_mutex(t_mutex *mutex)
{
	if (pthread_mutex_destroy(mutex->lock) != 0
		|| pthread_mutex_destroy(mutex->msg) != 0
		|| pthread_mutex_destroy(mutex->mel) != 0)
		return (1);
	return (mutex->lock = NULL, mutex->msg = NULL, mutex->mel = NULL, 0);
}

int	free_all(t_philo *ph, pthread_mutex_t *fork, t_mutex *mutex)
{
	if (destroy_forks(fork, ph->args->num_of_philos)
		|| free_mutex(mutex))
		return (1);
	return (0);
}

void	init_arg(t_arg *arg, char **av)
{
	arg->num_of_philos = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_times_to_eat = -1;
	if (av[5])
		arg->num_times_to_eat = ft_atoi(av[5]);
}

t_philo	*init_ph(t_arg *args, pthread_mutex_t *forks, t_mutex *mutex)
{
	int		i;
	t_philo	*ph;

	ph = malloc(sizeof(t_philo) * args->num_of_philos);
	if (!ph)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		ph[i].philo_id = i + 1;
		ph[i].eating = false;
		ph[i].dead = &mutex->death;
		ph[i].meals = 0;
		ph[i].end_lock = mutex->lock;
		ph[i].message = mutex->msg;
		ph[i].meal = mutex->mel;
		ph[i].r_fork = &forks[i];
		ph[i].l_fork = &forks[(i + 1) % args->num_of_philos];
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].args = args;
		i++;
	}
	return (ph);
}
