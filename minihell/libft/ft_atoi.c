#include "libft.h"

int	ft_atoi(const char *str)
{
	int	r;
	int	n;

	r = 1;
	n = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n') || \
	(*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-')
		r = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + ((int) *str - '0');
		str++;
	}
	return (r * n);
}
