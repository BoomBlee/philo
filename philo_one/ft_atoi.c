
#include <unistd.h>

int			ft_atoi(const char *nptr)
{
	int		res;
	size_t	i;

	res = 0;
	i = 0;
	if (nptr[i] == '-')
		return (-1);
	// if ((nptr[i] > ' ' && nptr[i] < '0') || nptr[i] > '9')
	// 	return -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	// if ((nptr[i] > ' ' && nptr[i] < '0') || nptr[i] > '9')
	// 	return -1;
	return (res);
}
