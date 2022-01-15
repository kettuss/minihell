#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*t;
	unsigned char	*u;

	t = (unsigned char *)dst;
	u = (unsigned char *)src;
	if (!n || dst == src)
		return (t);
	while (n--)
		*t++ = *u++;
	return (dst);
}
