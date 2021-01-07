
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

int	main(int ac, char **av)
{
	if (parse_argv(ac, av) == -1)
		return -1;
	return 0;
}
