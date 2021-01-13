
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct	s_philo_one
{
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	pthread_mutex_t death;
	pthread_mutex_t	stop_eating;

	pthread_t		*thread;
	short int		life;
	struct timeval	start_time;
	size_t			time_of_life;
	size_t			number;
	struct timeval	start_proc;
	size_t			count_eating;
	short int		flag_print;
}				t_philo;

typedef struct	s_data
{
	size_t	quantity_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_eat;
	t_philo	*philo;
	short int	flag_print;
}				t_data;


int				ft_atoi(const char *nptr);
size_t			ft_strlen(const char *str);

