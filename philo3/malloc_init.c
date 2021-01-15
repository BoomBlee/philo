/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:37:32 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 09:43:10 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_allocate(pid_t **pid)
{
	if (!(*pid = malloc(g_data.quantity_philo * sizeof(pid_t))))
		return (-1);
	if (!(g_data.philo = malloc(g_data.quantity_philo * sizeof(t_philo))))
	{
		free(*pid);
		return (-1);
	}
	if (!(g_data.philo->thread = malloc(g_data.quantity_philo * sizeof(pthread_t))))
	{
		free(*pid);
		free(g_data.philo);
		return (-1);
	}
	return (0);
}

int		delete_sem(void)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop_eating");
	g_data.flag_print = 1;
	return (0);
}

int		free_malloc(void)
{
	free(g_data.philo);
	free(g_data.philo->thread);
	return (-1);
}

void	init_tmp(t_philo *tmp, sem_t *stop_eating, size_t i)
{
	tmp->flag_print = 1;
	tmp->number = i + 1;
	tmp->life = 1;
	tmp->time_of_life = g_data.time_to_die;
	tmp->stop_eating = stop_eating;
}

int		create_sem(pid_t *pid, sem_t *stop_eating)
{
	size_t		i;
	t_philo		*tmp;
	sem_t		*death;
	sem_t		*print;
	pthread_t	stopped;

	i = 0;
	death = sem_open("death", O_CREAT, S_IRWXU, 0);
	print = sem_open("print", O_CREAT, S_IRWXU, 1);
	stop_eating = sem_open("stop_eating", O_CREAT, S_IRWXU, 0);
	tmp = g_data.philo;
	g_data.flag_print = 1;
	while (i < g_data.quantity_philo)
	{
		init_tmp(&tmp[i], stop_eating, i);
		tmp[i].death = death;
		tmp[i].print = print;
		gettimeofday(&tmp[i].start_time, NULL);
		pid[i] = fork();
		if (pid[i] < 0)
			return (-1);//free malloc
		else if (pid[i] == 0)
		{
			function_philo_three(&tmp[i]);
			exit (0);
		}
		++i;
	}
	pthread_create(&stopped, NULL, function_stop_eat, tmp);
	return (0);
}
