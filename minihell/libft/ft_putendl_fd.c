#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	y;

	y = '\n';
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, &y, 1);
}
