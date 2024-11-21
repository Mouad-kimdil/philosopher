/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:26:09 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 23:51:47 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_l(t_philo *ph)
{
	pthread_mutex_lock(ph->end_lock);
	if (*ph->dead == 1)
	{
		pthread_mutex_unlock(ph->end_lock);
		return (true);
	}
	pthread_mutex_unlock(ph->end_lock);
	return (false);
}

void	print_message(t_philo *ph, char *message)
{
	size_t	time;

	pthread_mutex_lock(ph->message);
	time = time_now() - ph->start_time;
	if (!dead_l(ph))
		printf("%zu %d %s\n", time, ph->philo_id, message);
	pthread_mutex_unlock(ph->message);
}

int	start_philo(t_arg *args, t_philo *ph)
{
	pthread_t	thread;
	int			i;

	if (pthread_create(&thread, NULL, &detach, ph) != 0)
		return (1);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_create(&ph[i].thread, NULL, &routine, &ph[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(thread, NULL) != 0)
		return (1);
	while (i < args->num_of_philos)
	{
		if (pthread_join(ph[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mutex			mutex;
	t_arg			args;
	t_philo			*ph;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
		return (ft_putstr("invalid number of arguments\n", 2), 1);
	if (check_input(av))
		return (1);
	if (init_arg(&args, av))
		return (ft_putstr("number of philos more than 200\n", 2), 1);
	mutex.lock = mutex_end();
	mutex.msg = mutex_message();
	mutex.mel = mutex_meal();
	forks = mutex_fork(&args);
	mutex.death = 0;
	if (!forks || !mutex.lock || !mutex.msg || !mutex.mel)
		return (free_locks(&mutex, forks, args.num_of_philos), 1);
	ph = init_ph(&args, forks, &mutex);
	if (!ph)
		return (free_locks(&mutex, forks, args.num_of_philos), 1);
	start_philo(&args, ph);
	free_locks(&mutex, forks, args.num_of_philos);
	return (my_free((void **)&ph), 0);
}
