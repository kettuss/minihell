/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:13:06 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:13:07 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
