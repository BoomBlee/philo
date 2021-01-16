/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:36:52 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/16 03:24:00 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

size_t	get_time(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

int		main(int ac, char **av)
{
	size_t	i;
	pid_t	*pid;
	sem_t	*stop_eating;

	stop_eating = NULL;
	i = delete_sem();
	if (parse_argv(ac, av))
		return (-1);
	ft_allocate(&pid);
	g_data.flag_print = 1;
	if (create_sem(pid, stop_eating))
		return (free_malloc());
	while (i < g_data.quantity_philo)
	{
		waitpid(pid[i], NULL, 0);
		++i;
	}
	delete_sem();
	return (0);
}
