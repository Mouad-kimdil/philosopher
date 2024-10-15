#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_list
{
	pthread_mutex_t	a;
	pthread_mutex_t	b;
	pthread_mutex_t	c;
}	t_list;

void	*routine(void *arg)
{
	t_list *ph = (t_list *)arg;

	pthread_mutex_lock(&ph->a);
	printf("Thread has locked mutex A\n");
	pthread_mutex_unlock(&ph->a);

	pthread_mutex_lock(&ph->b);
	printf("Thread has locked mutex B\n");
	pthread_mutex_unlock(&ph->b);

	pthread_mutex_lock(&ph->c);
	printf("Thread has locked mutex C\n");
	pthread_mutex_unlock(&ph->c);

	return NULL;
}

int main(void)
{
	t_list	ph;
	int		size = 5;
	pthread_t	th[size];

	pthread_mutex_init(&ph.a, NULL);
	pthread_mutex_init(&ph.b, NULL);
	pthread_mutex_init(&ph.c, NULL);
	for (int i = 0; i < size; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, &ph) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread");
			return (2);
		}
	}
	pthread_mutex_destroy(&ph.a);
	pthread_mutex_destroy(&ph.b);
	pthread_mutex_destroy(&ph.c);

	return 0;
}
