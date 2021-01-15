/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 05:44:27 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 08:16:28 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	get_time(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

int		main(int ac, char **av)
{
	size_t			i;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*stop_eating;

	i = 0;
	g_data.flag_print = 1;
	if (parse_argv(ac, av))
		return (-1);
	if (ft_allocate(&fork, &stop_eating))
		return (free_malloc(fork, stop_eating));
	if (create_mutex(fork, stop_eating))
		return (free_malloc(fork, stop_eating));
	while (i < g_data.quantity_philo)
	{
		if (pthread_join(g_data.philo->thread[i], NULL))
			return (free_malloc(fork, stop_eating));
		++i;
	}
	return (0);
}
