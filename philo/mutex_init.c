/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:41:41 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/18 00:46:29 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int i)
{
	int	x;

	x = 0;
	while (x < i)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			return ;
		i++;
	}
	free(forks);
}

pthread_mutex_t	*mutex_fork(t_arg *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * args->num_of_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free_forks(forks, i), NULL);
		i++;
	}
	return (forks);
}

pthread_mutex_t	*mutex_end(t_arg *args)
{
	pthread_mutex_t	*end_lock;
	int				i;

	end_lock = malloc(sizeof(pthread_mutex_t) * args->num_of_philos);
	if (!end_lock)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_mutex_init(&end_lock[i], NULL) != 0)
			return (free_forks(end_lock, i), NULL);
		i++;
	}
	return (end_lock);
}

pthread_mutex_t	*mutex_message(t_arg *args)
{
	pthread_mutex_t	*message;
	int				i;

	message = malloc(sizeof(pthread_mutex_t) * args->num_of_philos);
	if (!message)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_mutex_init(&message[i], NULL) != 0)
			return (free_forks(message, i), NULL);
		i++;
	}
	return (message);
}

pthread_mutex_t	*mutex_meal(t_arg *args)
{
	pthread_mutex_t	*meal;
	int				i;

	meal = malloc(sizeof(pthread_mutex_t) * args->num_of_philos);
	if (!meal)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_mutex_init(&meal[i], NULL) != 0)
			return (free_forks(meal, i), NULL);
		i++;
	}
	return (meal);
}
