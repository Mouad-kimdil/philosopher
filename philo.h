/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:43:07 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/15 04:10:48 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_mutex
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	pthread_mutex_t	*meal;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	t_mutex			mutex;
} t_philo;

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