/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:36:50 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:36:51 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
