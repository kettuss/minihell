/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:14:12 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:14:13 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chkout(char c, const char *st)
{
	while (*st)
	{
		if (c == *st)
			return (1);
		st++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	l;
	size_t	u;
	size_t	z;

	l = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[l] && ft_chkout(s1[l], set))
		l++;
	z = ft_strlen(s1);
	while (z > l && ft_chkout(s1[z - 1], set))
		z--;
	str = (char *)malloc(sizeof(*s1) * (z - l + 1));
	if (!str)
		return (NULL);
	u = 0;
	while (l < z)
		str[u++] = s1[l++];
	str[u] = 0;
	return (str);
}
