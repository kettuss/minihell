#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] != 0)
	{	
		if (i + j + 1 < dstsize)
			dst[i + j] = src[j];
		j++;
	}	
	if (dstsize > i)
		dst[i + j] = '\0';
	return (i + j);
}
