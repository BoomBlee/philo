/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcaraway <kcaraway@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 07:37:48 by kcaraway          #+#    #+#             */
/*   Updated: 2021/01/16 03:15:39 by kcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>

typedef struct		s_philo_one
{
	sem_t			*fork;
	sem_t			*print;
	sem_t			*death;
	sem_t			*stop_eating;

	pthread_t		*thread;
	short int		life;
	struct timeval	start_time;
	size_t			time_of_life;
	size_t			number;
	struct timeval	start_proc;
	size_t			count_eating;
	short int		flag_print;
}					t_philo;

typedef struct		s_data
{
	size_t			quantity_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_eat;
	t_philo			*philo;
	short int		flag_print;
}					t_data;

/*
*******************  main.c  *******************
*/
size_t				get_time(struct timeval t1);
/*
*******************  pars.c  *******************
*/
int					parse_argv(int ac, char **av);
/*
*******************  malloc_init.c  *******************
*/
int					free_malloc(void);
int					delete_sem(void);
int					create_sem(sem_t *fork, sem_t *stop_eating);
/*
*******************  malloc_init.c  *******************
*/
void				*function_philo_two(void *star);
/*
*******************  malloc_init.c  *******************
*/
void				*stop(void *two);
void				*death(void *one);
void				*function_stop_eat(void *pid);
t_data				g_data;
#endif
