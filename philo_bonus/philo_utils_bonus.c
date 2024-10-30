/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:15:08 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 05:04:01 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sema(t_sema *sem)
{
	if (sem->dead)
	{
		sem_unlink("dead");
		sem_close(sem->dead);
	}
	if (sem->forks)
	{
		sem_unlink("forks");
		sem_close(sem->forks);
	}
	if (sem->meal)
	{
		sem_unlink("meal");
		sem_close(sem->meal);
	}
	if (sem->message)
	{
		sem_unlink("message");
		sem_close(sem->message);
	}
	if (sem->eated)
	{
		sem_unlink("eated");
		sem_close(sem->eated);
	}
}

void	print_message(t_philo *ph, char *s)
{
	sem_wait(ph->message_lock);
	printf("%zu %d %s\n", time_now() - ph->start_time, ph->philo_id, s);
	sem_post(ph->message_lock);
}

int	is_valid_number(char *str)
{
	int	i;

	if (str && !str[0])
		return (ft_putstr("input must be a number", 1), 1);
	i = -1;
	while (str[++i])
	{
		if (!is_number(str[i]))
			return (ft_putstr("input must be a number", 2), 1);
	}
	return (0);
}

int	check_overflow(char *str)
{
	int		i;
	long	nb;
	int		len;

	i = 0;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len > 10)
		return (ft_putstr("number is too big", 2), 1);
	nb = ft_atoi(str);
	if (nb > INT_MAX)
		return (ft_putstr("number is too big", 2), 1);
	if (nb <= 0)
		return (ft_putstr("number must be positive", 2), 1);
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (is_valid_number(av[i]) || check_overflow(av[i]))
			return (1);
	}
	return (0);
}
