/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:36:16 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:36:17 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
