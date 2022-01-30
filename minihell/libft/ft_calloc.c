#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*prt;

	prt = (char *)malloc(count * size);
	if (!prt)
		return (NULL);
	ft_memset (prt, 0, (count * size));
	return (prt);
}
