#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_t;
	unsigned char	*src_c;
	unsigned char	t;

	src_c = (unsigned char *)src;
	dst_t = (unsigned char *)dst;
	t = (unsigned char)c;
	if (!src && !dst)
		return (0);
	while (n--)
	{
		*dst_t++ = *src_c++;
		if (*(dst_t - 1) == t)
			return (dst_t);
	}
	return (NULL);
}
