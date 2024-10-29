/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:30:55 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/30 00:04:50 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	child(t_philo *ph)
{
	ph->pid = fork();
	if (ph->pid == -1)
		return (0);
	if (ph->pid == 0)
		philo_routine(ph);
	return (ph->pid);
}

int	check_philos_status(int *pids, t_philo *ph)
{
	int	status;
	int	meals;
	int	i;

	meals = 0;
	while (1)
	{
		i = 0;
		while (i < ph->args->num_of_philos)
		{
			waitpid(pids[i], &status, WNOHANG);
			if (WEXITSTATUS(status) == i)
			{
				printf("%zu %d %s\n", time_now() - ph->start_time, i + 1, DEAD);
				return (1);
			}
			if (WEXITSTATUS(status) == 212)
				(1) && (meals++, status = -1);
			if (meals == ph->args->num_of_philos)
				return (1);
			i++;
		}
		usleep(300);
	}
	return (0);
}

int	start_philo(t_philo *ph)
{
	int			*pids;
	int			i;

	pids = malloc(sizeof(int) * ph->args->num_of_philos);
	if (!pids)
		return (1);
	i = 0;
	while (i < ph->args->num_of_philos)
	{
		ph[i].i = i;
		pids[i] = child(&ph[i]);
		i++;
	}
	check_philos_status(pids, ph);
	i = 0;
	while (i < ph->args->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	return (0);
}

sem_t	*init_semaphores(char *s, int value)
{
	sem_t	*semaphore;

	sem_unlink(s);
	semaphore = sem_open(s, O_CREAT | O_EXCL, 0644, value);
	return (semaphore);
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*ph;
	t_sema	sem;

	if (ac != 5 && ac != 6)
		return (ft_putstr("invalid number of arguments\n", 2), 1);
	if (check_input(av))
		return (1);
	init_arg(&args, av);
	sem.message = init_semaphores("message", 1);
	sem.meal = init_semaphores("meal", 1);
	sem.eated = init_semaphores("eated", 1);
	sem.dead = init_semaphores("dead", 1);
	sem.forks = init_semaphores("forks", args.num_of_philos);
	ph = init_philo(&args, &sem);
	start_philo(ph);
}
