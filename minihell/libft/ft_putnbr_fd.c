#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		t;
	char	m[10];

	t = 10;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= (-1);
		}
		while (n > 0)
		{
			m[--t] = '0' + n % 10;
			n /= 10;
		}
		while (t < 10)
		{
			write(fd, &m[t++], 1);
		}
	}
}