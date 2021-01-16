/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_eat_think_sleep.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:37:36 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/16 03:53:47 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		function_eating(t_philo *tmp)
{
	sem_wait(tmp->fork);
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time),
		tmp->number);
	sem_post(tmp->print);
	sem_wait(tmp->fork);
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu has taken a fork\n", get_time(tmp->start_time),
		tmp->number);
	sem_post(tmp->print);
	gettimeofday(&tmp->start_proc, NULL);
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu \033[32mis eating\033[0m\n",
		get_time(tmp->start_time), tmp->number);
	sem_post(tmp->print);
	while (g_data.time_to_eat > get_time(tmp->start_proc))
		usleep(240);
	sem_post(tmp->fork);
	sem_post(tmp->fork);
}

static void		function_sleep(t_philo *tmp)
{
	struct timeval	start_sleep;

	gettimeofday(&start_sleep, NULL);
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu \033[33mis sleeping\033[0m\n",
		get_time(tmp->start_time), tmp->number);
	sem_post(tmp->print);
	while (g_data.time_to_sleep > get_time(start_sleep))
		usleep(240);
}

static void		function_think(t_philo *tmp)
{
	sem_wait(tmp->print);
	if (tmp->flag_print == 1 && g_data.flag_print == 1)
		printf("%lu %lu \033[36mis thinking\033[0m\n",
		get_time(tmp->start_time), tmp->number);
	sem_post(tmp->print);
}

static	void	*castil(t_philo *tmp, pthread_t one, pthread_t two)
{
	tmp->life = 0;
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	return (NULL);
}

void			*function_philo_two(void *star)
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
			break ;
		function_sleep(tmp);
		function_think(tmp);
	}
	sem_post(tmp->stop_eating);
	return (castil(tmp, one, two));
}
