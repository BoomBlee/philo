
#include <unistd.h>

static int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

int			ft_atoi(const char *nptr)
{
	int res;
	int minus;

	res = 0;
	minus = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (!(ft_memcmp(nptr, "-2147483648", 11)))
		return (-2147483648);
	if (*nptr == '-')
		minus = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
		if (res < 0 && minus == -1)
			return (0);
		else if (res < 0)
			return (-1);
	}
	return (res * minus);
}