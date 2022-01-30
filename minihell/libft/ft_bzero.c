#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*t;

	t = s;
	while (n--)
		t[n] = '\0';
	s = t;
}
