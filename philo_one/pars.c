/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 04:46:46 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 05:01:08 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_atoi(const char *nptr)
{
	int		res;
	size_t	i;

	res = 0;
	i = 0;
	if (nptr[i] == '-')
		return (0);
	if ((nptr[i] > ' ' && nptr[i] < '0') || nptr[i] > '9')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	if ((nptr[i] > ' ' && nptr[i] < '0') || nptr[i] > '9')
		return (0);
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int		parse_argv(int ac, char **av)
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
