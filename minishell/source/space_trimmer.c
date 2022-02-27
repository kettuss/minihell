/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_trimmer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:27:40 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 20:00:58 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	qoutes_trim(t_cmd **cmd)
{
	int		i;
	char	*temp;
	t_cmd	*old_cmd;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	old_cmd = *cmd;
	while (*cmd)
	{
		i = 0;
		while ((*cmd)->cmd[++i])
		{
			temp = (*cmd)->cmd[i];
			(*cmd)->cmd[i] = ft_strtrim((*cmd)->cmd[i], "\'\"");
			free(temp);
		}
		*cmd = (*cmd)->next;
	}
	*cmd = old_cmd;
}

char	*replace_pointer(char *new_str)
{
	return (new_str);
}

int	len_newstr_utils(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	i--;
	return (i);
}

int	len_new_str(char *str)
{
	int		i;
	int		len;
	char	c;

	i = -1;
	len = 0;
	while (str[++i])
	{
		c = str[i];
		if (c == '\'' || c == '\"')
		{
			while (str[i] && str[++i] != c)
				len++;
			len += 2;
			continue ;
		}
		else if (c == ' ')
		{
			len++;
			i = len_newstr_utils(str, i);
			continue ;
		}
		len++;
	}
	return (len);
}

char	*spc_trim(char *str)
{
	int		i;
	int		position;
	char	*new_str;

	i = -1;
	position = 0;
	new_str = str;
	str = ft_strtrim(str, " ");
	free(new_str);
	new_str = (char *)malloc(sizeof(char) * (len_new_str(str) + 1));
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			new_str[position++] = str[i];
			while (str[i] == ' ')
				i++;
		}
		new_str[position++] = str[i];
	}
	new_str[position] = '\0';
	free(str);
	return (new_str);
}
