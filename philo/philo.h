	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   philo.h                                            :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: shisui <shisui@student.42.fr>              +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/10/15 00:43:07 by mkimdil           #+#    #+#             */
	/*   Updated: 2024/10/17 06:25:03 by shisui           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#ifndef PHILO_H
	# define PHILO_H

	# include <stdio.h>
	# include <stdlib.h>
	# include <unistd.h>
	# include <pthread.h>
	# include <stdbool.h>
	# include <limits.h>
	# include <sys/time.h>

	typedef struct s_arg
	{
		int				num_of_philos;
		size_t			time_to_die;
		size_t			time_to_eat;
		size_t			time_to_sleep;
		int				num_times_to_eat;
	} t_arg;

	typedef struct s_philo
	{
		pthread_t		thread;
		int				philo_id;
		bool			eating;
		bool			dead;
		int				meals;
		pthread_mutex_t	end_lock;
		pthread_mutex_t	message;
		pthread_mutex_t	meal;
		pthread_mutex_t	*l_fork;
		pthread_mutex_t	*r_fork;
		size_t			start_time;
		size_t			last_meal_time;
		t_arg			*args;
	} t_philo;

	# define TAKE_FORK "has taken a fork\n"
	# define DROP_FORK "has dropped a fork\n"
	# define EAT "is eating\n"
	# define SLEEP "is sleeping\n"
	# define THINK "is thinking\n"
	# define DEAD "is dead\n"

	void	ft_putchar(char c, int fd);
	void	ft_putstr(char *s, int fd);
	int		is_number(int c);
	int		is_valid_number(char *str);
	int		check_input(char **av);
	int		ft_strlen(char *str);
	long	ft_atoi(char *str);
	int		ft_usleep(size_t milliseconds);
	size_t	get_current_time(void);

	#endif