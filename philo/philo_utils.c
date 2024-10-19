/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:42:59 by mkimdil           #+#    #+#             */
/*   Updated: 2024/10/19 22:51:20 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
