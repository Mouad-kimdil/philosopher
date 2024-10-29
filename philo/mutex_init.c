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

pthread_mutex_t	*mutex_end(void)
{
	pthread_mutex_t	*end_lock;

	end_lock = malloc(sizeof(pthread_mutex_t));
	if (!end_lock)
		return (NULL);
	if (pthread_mutex_init(end_lock, NULL) != 0)
		return (NULL);
	return (end_lock);
}

pthread_mutex_t	*mutex_message(void)
{
	pthread_mutex_t	*message;

	message = malloc(sizeof(pthread_mutex_t));
	if (!message)
		return (NULL);
	if (pthread_mutex_init(message, NULL) != 0)
		return (NULL);
	return (message);
}

pthread_mutex_t	*mutex_meal(void)
{
	pthread_mutex_t	*meal;

	meal = malloc(sizeof(pthread_mutex_t));
	if (!meal)
		return (NULL);
	if (pthread_mutex_init(meal, NULL) != 0)
		return (NULL);
	return (meal);
}
