/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:37:32 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/16 03:15:32 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			delete_sem(void)
{
	sem_unlink("fork");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop_eating");
	g_data.flag_print = 1;
	return (0);
}

int			free_malloc(void)
{
	free(g_data.philo);
	free(g_data.philo->thread);
	return (-1);
}

static void	init_tmp(t_philo *tmp, sem_t *fork, sem_t *stop_eating, size_t i)
{
	tmp->flag_print = 1;
	tmp->number = i + 1;
	tmp->life = 1;
	tmp->time_of_life = g_data.time_to_die;
	tmp->fork = fork;
	tmp->stop_eating = stop_eating;
}

static int	protect_pthread(t_philo *tmp, size_t i)
{
	g_data.flag_print = 1;
	if (pthread_create(&g_data.philo->thread[i], NULL, function_philo_two,
	&tmp[i]))
		return (1);
	return (0);
}

int			create_sem(sem_t *fork, sem_t *stop_eating)
{
	size_t		i;
	t_philo		*tmp;
	sem_t		*death;
	sem_t		*print;
	pthread_t	stopped;

	i = 0;
	fork = sem_open("fork", O_CREAT, S_IRWXU, g_data.quantity_philo);
	death = sem_open("death", O_CREAT, S_IRWXU, 0);
	print = sem_open("print", O_CREAT, S_IRWXU, 1);
	stop_eating = sem_open("stop_eating", O_CREAT, S_IRWXU, 0);
	tmp = g_data.philo;
	if (pthread_create(&stopped, NULL, function_stop_eat, tmp))
		return (1);
	while (i < g_data.quantity_philo)
	{
		init_tmp(&tmp[i], fork, stop_eating, i);
		tmp[i].death = death;
		tmp[i].print = print;
		gettimeofday(&tmp[i].start_time, NULL);
		if (protect_pthread(tmp, i))
			return (1);
		++i;
	}
	return (0);
}
