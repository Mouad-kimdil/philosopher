#include "philo.h"

void	init_arg(t_arg *arg, char **av)
{
	arg->num_of_philos = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_times_to_eat = -1;
	if (av[5])
		arg->num_times_to_eat = ft_atoi(av[5]);
}

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

t_philo	*init_ph(t_arg *args, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*ph;

	ph = malloc(sizeof(t_philo) * args->num_of_philos);
	if (!ph)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		ph[i].philo_id = i + 1;
		ph[i].eating = false;
		ph[i].dead = false;
		ph[i].meals = 0;
		pthread_mutex_init(&ph[i].end_lock, NULL);
		pthread_mutex_init(&ph[i].message, NULL);
		pthread_mutex_init(&ph[i].meal, NULL);
		ph[i].r_fork = &forks[i];	
		ph[i].l_fork = &forks[(i + 1) % args->num_of_philos];
		ph[i].start_time = get_current_time();
		ph[i].last_meal_time = get_current_time();
		ph[i].args = args;
		i++;
	}
	return (ph);
}

bool	dead_l(t_philo *ph)
{
	pthread_mutex_lock(&ph->end_lock);
	if (ph->dead == true)
	{
		pthread_mutex_unlock(&ph->end_lock);
		return (true);
	}
	pthread_mutex_unlock(&ph->end_lock);
	return (false);
}

void	print_message(t_philo *ph, char *message)
{
	size_t	time;

	pthread_mutex_lock(&ph->message);
	time = get_current_time() - ph->start_time;
	if (!dead_l(ph))
		printf("%zu %d %s\n", time, ph->philo_id, message);
	pthread_mutex_unlock(&ph->message);
}

void	sleep_routine(t_philo *ph)
{
	print_message(ph, EAT);
	ft_usleep(ph->args->time_to_sleep);
}

void	think_routine(t_philo *ph)
{
	print_message(ph, THINK);
}

void	eat_routine(t_philo *ph)
{
	pthread_mutex_lock(ph->r_fork);
	print_message(ph, TAKE_FORK);
	if (ph->args->num_of_philos == 1)
	{
		ft_usleep(ph->args->time_to_die);
		pthread_mutex_unlock(ph->r_fork);
		return ;
	}
	pthread_mutex_lock(ph->l_fork);	
	print_message(ph, TAKE_FORK);
	ph->eating = true;
	print_message(ph, EAT);
	pthread_mutex_lock(&ph->meal);
	ph->last_meal_time = get_current_time();
	ph->meals++;
	pthread_mutex_unlock(&ph->meal);
	ft_usleep(ph->args->time_to_eat);
	ph->eating = false;
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!dead_l(ph))
	{
		eat_routine(ph);
		sleep_routine(ph);
		think_routine(ph);
	}
	return (arg);
}

bool	philo_dead(t_philo *ph, size_t time_to_die)
{
	pthread_mutex_lock(&ph->meal);
	if (get_current_time() - ph->last_meal_time	>= time_to_die
		&& ph->eating == false)
		return (pthread_mutex_unlock(&ph->meal), true);
	pthread_mutex_unlock(&ph->meal);
	return (false);
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
			pthread_mutex_lock(&ph[0].end_lock);
			ph->dead = 1;
			pthread_mutex_unlock(&ph[0].end_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_is_eat(t_philo *ph)
{
	int	i;
	int	finish;

	i = 0;
	finish = 0;
	if (ph[i].args->num_times_to_eat == -1)
		return (false);
	while (i < ph[0].args->num_of_philos)
	{
		pthread_mutex_lock(&ph[i].meal);
		if (ph[i].meals >= ph[i].args->num_times_to_eat)
			finish++;
		pthread_mutex_unlock(&ph[i].meal);
		i++;
	}
	if (finish == ph[0].args->num_of_philos)
	{
		pthread_mutex_lock(&ph[0].end_lock);
		ph->dead = true;
		pthread_mutex_unlock(&ph[0].end_lock);
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
		if (check_is_dead(ph) == true || check_is_eat(ph) == true)
			break ;
	}
	return (arg);
}

int	start_philo(t_arg *args, t_philo *ph)
{
	pthread_t	thread;
	int			i;

	if (pthread_create(&thread, NULL, &deatach, ph) != 0)
		return (1);	
	i = 0;
	while (i < args->num_of_philos)
	{
		if (pthread_create(&ph[i].thread, NULL, &routine, (void *)&ph[i]) != 0)
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

int main(int ac, char **av)
{
	t_arg			args;
	t_philo			*ph;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
		return (ft_putstr("invalid number of arguments\n", 2), 1);
	if (check_input(av))
		return (1);
	init_arg(&args, av);
	forks = mutex_fork(&args);
	if (!forks)
		return (EXIT_FAILURE);
	ph = init_ph(&args, forks);
	if (!ph)
		return (EXIT_FAILURE);
	start_philo(&args, ph);
	return (0);
}
