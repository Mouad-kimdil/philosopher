/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 02:29:35 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 02:36:10 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_free(void **arg)
{
	if (arg && *arg)
	{
		free(*arg);
		*arg = NULL;
	}
}

void	free_locks(t_mutex *mutex, pthread_mutex_t *forks, int num)
{
	int	i;

	if (mutex->lock)
	{
		pthread_mutex_destroy(mutex->lock);
		my_free((void **)&mutex->lock);
	}
	if (mutex->mel)
	{
		pthread_mutex_destroy(mutex->mel);
		my_free((void **)&mutex->mel);
	}
	if (mutex->msg)
	{
		pthread_mutex_destroy(mutex->msg);
		my_free((void **)&mutex->msg);
	}
	if (forks)
	{
		i = -1;
		while (++i < num)
			pthread_mutex_destroy(&forks[i]);
		my_free((void **)&forks);
	}
}
