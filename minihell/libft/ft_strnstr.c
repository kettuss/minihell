/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:37:00 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:37:01 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	t;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		t = 0;
		while (haystack[i + t] && needle[t] && i + t < len && \
		haystack[i + t] == needle[t])
			t++;
		if (!needle[t])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
