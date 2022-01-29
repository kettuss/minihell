#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	t;

	t = 0;
	if (!dst && !src)
		return (0);
	if (dstsize > 0)
	{
		while (src[t] && t < dstsize - 1)
		{
			dst[t] = src[t];
			t++;
		}
		dst[t] = '\0';
	}
	while (src[t])
		t++;
	return (t);
}
