#include "libft.h"

static int	ft_prnbr(long int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			nel;
	long int	n_;

	n_ = n;
	nel = ft_prnbr(n);
	str = (char *)malloc(sizeof(char)*(nel + 1));
	if (!str)
		return (NULL);
	if (n_ < 0)
	{
		str[0] = '-';
		n_ = -n_;
	}
	else if (n_ == 0)
		str[0] = 0 + '0';
	str[nel] = '\0';
	while (n_ > 0)
	{
		nel--;
		str[nel] = (n_ % 10) + '0';
		n_ = n_ / 10;
	}
	return (str);
}
