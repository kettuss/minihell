/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:14:16 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:14:17 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*bgn;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	if (len <= ft_strlen(s + start))
		bgn = (char *)malloc(sizeof(char) * (len + 1));
	else
		bgn = (char *)malloc(sizeof(char) * (ft_strlen(s + start)));
	if (!bgn)
		return (NULL);
	while (s[i] && start < ft_strlen(s))
	{
		if (i >= start && l < len)
			bgn[l++] = s[i];
		i++;
	}
	bgn[l] = '\0';
	return (bgn);
}
