/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:19:22 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/15 03:31:40 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_philo *ph, char **av)
{
	ph->num_of_philos = ft_atoi(av[1]);
	ph->time_to_eat = ft_atoi(av[2]);
	ph->time_to_die = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ph->num_times_to_eat = ft_atoi(av[5]);
	else
		ph->num_times_to_eat = 0;
}

void	printf_args(t_philo *ph)
{
	printf("number of philosophers: %d\ntime a philosopher will die if he doesn't eat: %zu\n\
time it takes a philosopher to eat: %zu\ntime it takes a philosopher to sleep: %zu\n\
Number of times all the philosophers need to eat before terminating the program: %d\n",
ph->num_of_philos, ph->time_to_eat, ph->time_to_die, ph->time_to_sleep, ph->num_times_to_eat);
}

int main(int ac, char **av)
{
	t_philo	ph;

	if (ac != 5 && ac != 6)
		return (ft_putstr("invalid number of arguments\n", 2), 1);
	if (check_input(av))
		return (1);
	init_struct(&ph, av);
	printf_args(&ph);
	return (0);
}
