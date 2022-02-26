/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:13:31 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:13:32 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	t;
	int	i;

	t = 0;
	i = 0;
	while (s[i] != '\0')
	{	
		if (s[i] != c)
		{
			t++;
			while (s[i] != c && s[i + 1] != '\0')
				i++;
		}
		i++;
	}
	return (t);
}

char	**ft_fremem(char **s)
{
	int	t;

	t = 0;
	while (s[t])
	{
		free(s[t]);
		s[t] = NULL;
		t++;
	}
	free(s);
	s = NULL;
	return (s);
}

static char	**ft_chcct(const char *s, char c, char **t, int u)
{
	int	cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	j = ft_count(s, c);
	while (u < j)
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			cnt++;
		}
		t[u] = ft_substr(s, i - cnt, cnt);
		if (!t[u])
			return (ft_fremem(t));
		cnt = 0;
		u++;
	}
	t[u] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	char	**t;

	i = 0;
	if (!s)
		return (NULL);
	y = ft_count(s, c);
	t = (char **)malloc(sizeof(char *) * (y + 1));
	if (!t)
		return (NULL);
	if (y == 0)
	{
		t[0] = NULL;
		return (t);
	}
	t = ft_chcct(s, c, t, 0);
	return (t);
}
