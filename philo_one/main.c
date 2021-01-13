
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
		return (error_exit("wrong number of philo\n"));
	if ((g_data.time_to_die = ft_atoi(av[2])) < 1)
		return (error_exit("wrong time to die\n"));
	if ((g_data.time_to_eat = ft_atoi(av[3])) < 1)
		return (error_exit("wrong time to eat\n"));
	if ((g_data.time_to_sleep = ft_atoi(av[4])) < 1)
		return (error_exit("wrong time to sleep\n"));
	if (ac == 6)
		if ((g_data.number_of_eat = ft_atoi(av[5])) < 1)
			return (error_exit("wrong number of eat\n"));
	return (0);
}

size_t	get_time(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

void	function_death_print(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu \033[1;31mdied\033[0m\n", get_time(tmp->start_time), tmp->number);
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
		usleep(10);
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

void	function_eating(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->fork[tmp->number - 1]);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	if (tmp->number != g_data.quantity_philo)
		pthread_mutex_lock(&tmp->fork[tmp->number]);
	else
		pthread_mutex_lock(&tmp->fork[0]);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	gettimeofday(&tmp->start_proc, NULL);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu is eating\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
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
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu is sleeping\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	while (g_data.time_to_sleep > get_time(start_sleep))
		usleep(10);
}

void	function_think(t_philo *tmp)
{
	// lock
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1)
		printf("%lu %lu is thinking\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	// unlock
}

void	*function_philo_one(void *star)
{
	t_philo		*tmp;
	pthread_t	one;
	pthread_t	two;
	size_t		count_eat;

	count_eat = 0;
	tmp = star;
	tmp->start_proc = tmp->start_time;
	while (tmp->number % 2 && get_time(tmp->start_proc) < g_data.time_to_eat)
		usleep(10);
	pthread_create(&one, NULL, death, tmp);
	pthread_create(&two, NULL, stop, tmp);

	while (tmp->life == 1)
	{
		function_eating(tmp);
		if (++count_eat == g_data.number_of_eat)
		{
			pthread_mutex_unlock(&tmp->death);
			break ;
		}
		function_sleep(tmp);
		function_think(tmp);
	}
	tmp->life = 0;
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	return (NULL);
}

void	*function_stop_eat(void *pid)
{
	t_philo		*tmp;

	tmp = pid;
	pthread_mutex_lock(&tmp->stop_eating);
	return (NULL);
}

int	main(int ac, char **av)
{
	size_t 	i;
	t_philo *tmp;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*stop_eating;
	pthread_t		stopped;

	i = 0;
	if (parse_argv(ac, av) == -1)
		return (-1);
	// printf("philo=%ld, die=%ld, eat=%ld, sleep=%ld\n", g_data.quantity_philo, g_data.time_to_die, g_data.time_to_eat, g_data.time_to_sleep);
	g_data.philo = malloc(g_data.quantity_philo * sizeof(t_philo));

	fork = malloc(g_data.quantity_philo * sizeof(pthread_mutex_t));
	g_data.philo->thread = malloc(g_data.quantity_philo * sizeof(pthread_t));

	pthread_mutex_init(&death, NULL);
	pthread_mutex_init(&print, NULL);
	
	stop_eating = malloc(g_data.quantity_philo * sizeof(pthread_mutex_t));

	tmp = g_data.philo;
	pthread_mutex_lock(&death);
	while (i < g_data.quantity_philo)
	{
		tmp[i].fork = fork;
		tmp[i].stop_eating = stop_eating[i];
		pthread_mutex_init(&tmp[i].stop_eating, NULL);//
		pthread_mutex_init(&tmp[i].fork[i], NULL);//
		gettimeofday(&tmp[i].start_time, NULL);
		tmp[i].flag_print = 1;
		tmp[i].number = i + 1;
		tmp[i].life = 1;
		tmp[i].death = death;
		tmp[i].print = print;
		tmp[i].time_of_life = g_data.time_to_die;
		pthread_create(&g_data.philo->thread[i], NULL, function_philo_one, &tmp[i]);
		++i;
	}
	i = 0;
	pthread_create(&stopped, NULL, function_stop_eat, tmp);
	while (i < g_data.quantity_philo)
	{
		pthread_join(g_data.philo->thread[i], NULL);
		++i;
	}
	return (0);
}
