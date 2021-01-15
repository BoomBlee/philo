
#include "philo_one.h"

void	function_death_print(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
	{
		g_data.flag_print = 0;
		printf("%lu %lu \033[1;31mdied\033[0m\n", get_time(tmp->start_time),
		tmp->number);
	}
	pthread_mutex_unlock(&tmp->death);
	usleep(g_data.quantity_philo * 100);
	pthread_mutex_unlock(&tmp->print);
}

void	*death(void *one)
{
	t_philo		*tmp;
	size_t		diff_time;

	tmp = one;
	while (tmp->life == 1)
	{
		if (tmp->time_of_life < (diff_time = get_time(tmp->start_proc)))
			function_death_print(tmp);
		usleep(100);
	}
	return (NULL);
}

void	*stop(void *two)
{
	t_philo		*tmp;

	tmp = two;
	pthread_mutex_lock(&tmp->death);
	tmp->life = 0;
	tmp->flag_print = 0;
	pthread_mutex_unlock(&tmp->death);
	return (0);
}

void	*function_stop_eat(void *pid)
{
	t_philo		*tmp;

	tmp = pid;
	pthread_mutex_lock(&tmp->stop_eating);
	return (NULL);
}
