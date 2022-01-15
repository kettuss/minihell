#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*t;

	if (n == 0)
		return (destination);
	t = destination;
	while (n--)
	{
		*t = (unsigned char)c;
		t++;
	}
	return (destination);
}
