
#include "philo_one.h"

t_data g_data;

int	error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	return -1;
}

int	parse_argv(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (error_exit("error argv\n"));
	if ((g_data.quantity_philo = ft_atoi(av[1])) < 2)
		return (error_exit("philo <= 1\n"));
	if ((g_data.time_to_die = ft_atoi(av[2])) < 1)
		return (error_exit("time to die < 1\n"));
	if ((g_data.time_to_eat = ft_atoi(av[3])) < 1)
		return (error_exit("time to eat < 1\n"));
	if ((g_data.time_to_sleep = ft_atoi(av[4])) < 1)
		return (error_exit("time to sleep < 1\n"));
	if (ac == 6)
		if ((g_data.number_of_eat = ft_atoi(av[5])) < 1)
			return (error_exit("number of eat < 1\n"));
	return 0;
}


size_t	get_time(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

void	function_death_print(t_philo *tmp)
{
	pthread_mutex_unlock(tmp->death);
	printf("%lu %lu died\n", get_time(tmp->start_time), tmp->number);
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
		usleep(10);
	}
	return (NULL);
}

void	*stop(void *two)
{
	t_philo		*tmp;

	tmp = two;
	pthread_mutex_lock(tmp->death);
	tmp->life = 0;
	pthread_mutex_unlock(tmp->death);
	return 0;
}

void	function_eating(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->fork[tmp->number - 1]);
	printf("%lu %lu has taken a fork\n", get_time(tmp->start_time), tmp->number);
	if (tmp->number != g_data.quantity_philo)
		pthread_mutex_lock(&tmp->fork[tmp->number]);
	else
		pthread_mutex_lock(&tmp->fork[0]);
	printf("%lu %lu has taken a fork\n", get_time(tmp->start_time), tmp->number);
	gettimeofday(&tmp->start_proc, NULL);
	printf("%lu %lu is eating\n", get_time(tmp->start_time), tmp->number);
	while (g_data.time_to_eat > get_time(tmp->start_proc))
		usleep(10);
	pthread_mutex_unlock(&tmp->fork[tmp->number - 1]);
	if (tmp->number != g_data.quantity_philo)
		pthread_mutex_unlock(&tmp->fork[tmp->number]);
	else
		pthread_mutex_unlock(&tmp->fork[0]);
}

void	function_sleep(t_philo *tmp)
{
	struct timeval	start_sleep;

	gettimeofday(&start_sleep, NULL);
	printf("%lu %lu is sleeping\n", get_time(tmp->start_time), tmp->number);
	while (g_data.time_to_sleep > get_time(start_sleep))
		usleep(10);
}

void	function_think(t_philo *tmp)
{
	printf("%lu %lu is thinking\n", get_time(tmp->start_time), tmp->number);
}

void	*function_philo_one(void *star)
{
	t_philo		*tmp;
	pthread_t	one;
	pthread_t	two;

	tmp = star;
	tmp->start_proc = tmp->start_time;
	while (tmp->number % 2 && get_time(tmp->start_proc) < g_data.time_to_eat)
		usleep(10);
	pthread_create(&one, NULL, death, tmp);
	pthread_create(&two, NULL, stop, tmp);

	while (tmp->life == 1)
	{
		function_eating(tmp);
		function_sleep(tmp);
		function_think(tmp);
	}
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	size_t 	i;
	t_philo *tmp;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;

	i = 0;
	if (parse_argv(ac, av) == -1)
		return -1;
	printf("philo=%ld, die=%ld, eat=%ld, sleep=%ld\n", g_data.quantity_philo, g_data.time_to_die, g_data.time_to_eat, g_data.time_to_sleep);
	g_data.philo = malloc(g_data.quantity_philo * sizeof(t_philo));

	fork = malloc(g_data.quantity_philo * sizeof(pthread_mutex_t));
	g_data.philo->thread = malloc(g_data.quantity_philo * sizeof(pthread_t));

	pthread_mutex_init(&death, NULL);
	pthread_mutex_init(&print, NULL);

	tmp = g_data.philo;
	pthread_mutex_lock(&death);
	while (i < g_data.quantity_philo)
	{
		tmp[i].fork = fork;
		pthread_mutex_init(&tmp->fork[i], NULL);//
		gettimeofday(&tmp[i].start_time, NULL);
		tmp[i].number = i + 1;
		tmp[i].life = 1;
		tmp[i].death = &death;
		tmp[i].print = &print;
		tmp[i].time_of_life = g_data.time_to_die;
		pthread_create(&g_data.philo->thread[i], NULL, function_philo_one, &tmp[i]);
		++i;
	}
	i = 0;
	while (i < g_data.quantity_philo)
	{
		pthread_join(g_data.philo->thread[i], NULL);
		++i;
	}
	return 0;
}
