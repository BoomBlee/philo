/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:44:10 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 22:47:40 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		delete_pid(pid_t *pid, size_t last)
{
	size_t i;

	i = 0;
	sem_post(g_data.philo->death);
	while (i < last)
	{
		waitpid(pid[i], NULL, 0);
		++i;
	}
	return (1);
}

int		delete_sem(void)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop_eating");
	g_data.flag_print = 1;
	return (0);
}
