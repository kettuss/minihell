/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:53:06 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:53:29 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_argv(char **good_bye)
{
	int	i;

	i = -1;
	if (!good_bye || !*good_bye)
		return ;
	while (good_bye[++i])
		free(good_bye[i]);
	free(good_bye);
}

int	redirect_count(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
			count++;
	return (count * 2);
}

char	**record_redicts(char **argv)
{
	int		str;
	int		i;
	char	**temp;

	str = 0;
	i = 0;
	if (redirect_count(argv) == 0)
		return (NULL);
	temp = (char **)malloc((redirect_count(argv) + 1) * sizeof(char *));
	while (argv[str])
	{
		if (!ft_strcmp(argv[str], ">>") || !ft_strcmp(argv[str], ">") || \
		!ft_strcmp(argv[str], "<") || \
		!ft_strcmp(argv[str], "<<"))
		{
			temp[i] = ft_strdup(argv[str]);
			temp[i + 1] = ft_strdup(argv[str + 1]);
			i += 2;
			str += 2;
			continue ;
		}
		str++;
	}
	temp[i] = NULL;
	return (temp);
}

char	**rewrite_cmd(char **argv)
{
	int		i;
	int		str;
	char	**temp;

	i = 0;
	str = 0;
	temp = (char **)malloc(((lentab(argv) - redirect_count(argv)) + 1) * \
	sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
		{
			i += 2;
			continue ;
		}
		temp[str] = ft_strdup(argv[i]);
		str++;
		i++;
	}
	temp[str] = NULL;
	return (temp);
}

void	cmd_run(t_cmd **cmd)
{
	t_cmd		*temp;
	char		**ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->cmd;
		if (!ar || !*ar)
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		(*cmd)->redicts = record_redicts(ar);
		if (!(*cmd)->redicts)
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		(*cmd)->cmd = rewrite_cmd(ar);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}
