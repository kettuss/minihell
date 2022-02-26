/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:21:58 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:35:10 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lentab(char **ms)
{
	int	i;

	i = -1;
	while (ms[++i])
		;
	return (i);
}

char	**argv_dup(char **ar)
{
	int		i;
	char	**copy;

	i = -1;
	copy = (char **)malloc(sizeof(char *) * (lentab(ar) + 1));
	copy[lentab(ar)] = NULL;
	while (ar[++i])
		copy[i] = ft_strdup(ar[i]);
	return (copy);
}

t_cmd	*lst_init(char **list)
{
	t_cmd	*element;

	element = (t_cmd *)malloc(sizeof(t_cmd));
	element->next = NULL;
	element->back = NULL;
	element->redicts = NULL;
	element->fd_heredoc = -1;
	element->fd_in = -1;
	element->fd_out = -1;
	element->cmd = argv_dup(list);
	return (element);
}

void	lst_add(t_cmd **cmd, t_cmd *element)
{
	if (!(*cmd))
	{
		*cmd = element;
		return ;
	}
	element->next = *cmd;
	(*cmd)->back = element;
	(*cmd) = element;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1[i] && !s2[i])
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
