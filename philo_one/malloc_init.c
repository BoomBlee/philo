
#include "philo_one.h"

int		ft_allocate(pthread_mutex_t **fork, pthread_mutex_t **stop_eating)
{
	if (!(g_data.philo = malloc(g_data.quantity_philo * sizeof(t_philo))))
		return (1);
	if (!(*fork = malloc(g_data.quantity_philo * sizeof(pthread_mutex_t))))
	{
		free(g_data.philo);
		return (1);
	}
	if (!(g_data.philo->thread =
	malloc(g_data.quantity_philo * sizeof(pthread_t))))
	{
		free(g_data.philo);
		free(fork);
		return (1);
	}
	if (!(*stop_eating =
	malloc(g_data.quantity_philo * sizeof(pthread_mutex_t))))
	{
		free(g_data.philo);
		free(fork);
		free(g_data.philo->thread);
		return (1);
	}
	return (0);
}

int		free_malloc(pthread_mutex_t *fork, pthread_mutex_t *stop_eating)
{
	free(stop_eating);
	free(g_data.philo);
	free(fork);
	free(g_data.philo->thread);
	return (-1);
}

void	init_tmp(t_philo *tmp, pthread_mutex_t *fork,
	pthread_mutex_t *stop_eating, size_t i)
{
	tmp->fork = fork;
	tmp->flag_print = 1;
	tmp->life = 1;
	tmp->time_of_life = g_data.time_to_die;
	tmp->number = i + 1;
}

int		create_mutex(pthread_mutex_t *fork, pthread_mutex_t *stop_eating)
{
	size_t			i;
	t_philo			*tmp;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_t		stopped;

	i = 0;
	if (pthread_mutex_init(&death, NULL) || pthread_mutex_init(&print, NULL)
	|| pthread_mutex_lock(&death))
		return (1);
	tmp = g_data.philo;
	while (i < g_data.quantity_philo)
	{
		tmp[i].death = death;
		tmp[i].print = print;
		init_tmp(&tmp[i], fork, stop_eating, i);
		tmp[i].stop_eating = stop_eating[i];
		if (pthread_create(&g_data.philo->thread[i], NULL, function_philo_one,
		&tmp[i]) || gettimeofday(&tmp[i].start_time, NULL) ||
		pthread_mutex_init(&tmp[i].fork[i], NULL) ||
		pthread_mutex_init(&tmp[i].stop_eating, NULL))
			return (1);
		++i;
	}
	return (pthread_create(&stopped, NULL, function_stop_eat, tmp));
}
