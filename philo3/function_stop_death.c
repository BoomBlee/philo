/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_stop_death.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:37:43 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 09:41:23 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	function_death_print(t_philo *tmp)
{
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
	{
		g_data.flag_print = 0;
		printf("%lu %lu \033[1;31mdied\033[0m\n", get_time(tmp->start_time),
		tmp->number);
	}
	sem_post(tmp->death);
	usleep(g_data.quantity_philo * 100);
	sem_post(tmp->print);
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
	sem_wait(tmp->death);
	tmp->life = 0;
	tmp->flag_print = 0;
	sem_post(tmp->death);
	return (0);
}

void	*function_stop_eat(void *pid)
{
	t_philo		*tmp;
	size_t		i;

	tmp = pid;
	i = 0;
	while (i++ < g_data.quantity_philo)
		sem_wait(tmp->stop_eating);
	sem_post(tmp->death);
	return (NULL);
}
