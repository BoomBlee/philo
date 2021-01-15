/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:36:52 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 08:02:52 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t	get_time(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

int		main(int ac, char **av)
{
	size_t	i;
	sem_t	*fork;
	sem_t	*stop_eating;

	i = delete_sem();
	if (parse_argv(ac, av))
		return (-1);
	if (!(g_data.philo = malloc(g_data.quantity_philo * sizeof(t_philo))))
		return (-1);
	if (!(g_data.philo->thread = malloc(g_data.quantity_philo
		* sizeof(pthread_t))))
	{
		free(g_data.philo);
		return (-1);
	}
	if (create_sem(fork, stop_eating))
		return (free_malloc());
	while (i < g_data.quantity_philo)
	{
		if (pthread_join(g_data.philo->thread[i], NULL))
			return (free_malloc());
		++i;
	}
	delete_sem();
	return (0);
}
