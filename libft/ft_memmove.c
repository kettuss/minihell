/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:13:09 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:13:10 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ddst;
	unsigned char	*ssrc;

	ddst = (unsigned char *) dst;
	ssrc = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		while (len--)
			*ddst++ = *ssrc++;
	}
	else if (src < dst)
	{
		while (len--)
			ddst[len] = ssrc[len];
	}
	return (dst);
}
/*копия до опредленного момента*/