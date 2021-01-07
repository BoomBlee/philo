
# include <unistd.h>
# include <pthread.h>

typedef struct	s_philo_one
{
	pthread_mutex_t v;
	pthread_t		c;
}				t_philo;

typedef struct	s_data
{
	int		quantity_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	t_philo	*philo;

}				t_data;


int				ft_atoi(const char *nptr);
size_t			ft_strlen(const char *str);

