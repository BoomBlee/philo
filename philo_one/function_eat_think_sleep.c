/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_eat_think_sleep.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 08:19:06 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/15 08:27:50 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		function_eating(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->fork[tmp->number - 1]);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time),
		tmp->number);
	pthread_mutex_unlock(&tmp->print);
	(tmp->number != g_data.quantity_philo) ?
	pthread_mutex_lock(&tmp->fork[tmp->number]) :
	pthread_mutex_lock(&tmp->fork[0]);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time),
		tmp->number);
	pthread_mutex_unlock(&tmp->print);
	gettimeofday(&tmp->start_proc, NULL);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu is eating\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	while (g_data.time_to_eat > get_time(tmp->start_proc))
		usleep(240);
	pthread_mutex_unlock(&tmp->fork[tmp->number - 1]);
	(tmp->number != g_data.quantity_philo) ?
	pthread_mutex_unlock(&tmp->fork[tmp->number]) :
	pthread_mutex_unlock(&tmp->fork[0]);
}

static void		function_sleep(t_philo *tmp)
{
	struct timeval	start_sleep;

	gettimeofday(&start_sleep, NULL);
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu is sleeping\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
	while (g_data.time_to_sleep > get_time(start_sleep))
		usleep(240);
}

static void		function_think(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu is thinking\n", get_time(tmp->start_time), tmp->number);
	pthread_mutex_unlock(&tmp->print);
}

static	void	*castil(t_philo *tmp, pthread_t one, pthread_t two)
{
	tmp->life = 0;
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	return (NULL);
}

void			*function_philo_one(void *star)
{
	t_philo		*tmp;
	pthread_t	one;
	pthread_t	two;
	size_t		count_eat;

	count_eat = 0;
	tmp = star;
	tmp->start_proc = tmp->start_time;
	while (tmp->number % 2 && get_time(tmp->start_proc) < g_data.time_to_eat)
		usleep(240);
	if (pthread_create(&one, NULL, death, tmp) ||
	pthread_create(&two, NULL, stop, tmp))
		return (NULL);
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
	return (castil);
}
