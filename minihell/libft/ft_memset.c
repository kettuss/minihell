/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:36:24 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:36:25 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
