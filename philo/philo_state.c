/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shisui <shisui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:44:13 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/18 06:39:35 by shisui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool philo_dead(t_philo *ph, size_t time_to_die)
{
	bool	is_dead;

    pthread_mutex_lock(ph->meal);
    is_dead = (get_current_time() - ph->last_meal_time >= time_to_die && !ph->eating);
    pthread_mutex_unlock(ph->meal);
    return (is_dead);
}

bool	check_is_dead(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph[0].args->num_of_philos)
	{
		if (philo_dead(&ph[i], ph[i].args->time_to_die))
		{
			print_message(ph, DEAD);
			pthread_mutex_lock(ph[0].end_lock);
			*ph->dead = 1;
			pthread_mutex_unlock(ph[0].end_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool check_is_eat(t_philo *ph)
{
    int	i;
    int finish = 0;

	i = 0;
    pthread_mutex_lock(ph[0].end_lock);
    if (ph[0].args->num_times_to_eat == -1)
    {
        pthread_mutex_unlock(ph[0].end_lock);
        return (false);
    }
    pthread_mutex_unlock(ph[0].end_lock);
    while (i < ph[0].args->num_of_philos)
    {
        pthread_mutex_lock(ph[i].meal);
        if (ph[i].meals >= ph[i].args->num_times_to_eat)
            finish++;
        pthread_mutex_unlock(ph[i].meal);
        i++;
    }
    if (finish == ph[0].args->num_of_philos)
    {
        pthread_mutex_lock(ph[0].end_lock);
        *ph->dead = 1;
        pthread_mutex_unlock(ph[0].end_lock);
        return (true);
    }
    return (false);
}

void	*deatach(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (true)
	{
		while (!check_is_dead(ph) && !check_is_eat(ph))
			ft_usleep(100);
		break ;
	}
	return (arg);
}
