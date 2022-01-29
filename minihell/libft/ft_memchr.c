#include "libft.h"

void	*ft_memchr(const char *s, int c, size_t n)
{
	char	*t;

	t = (char *)s;
	while (n--)
	{
		if (*t == (char) c)
			return (t);
		else
			t++;
	}
	return (0);
}
