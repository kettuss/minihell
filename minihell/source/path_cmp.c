/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:34:08 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 00:34:13 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*path_cmp(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*maybe_path;

	i = -1;
	if (!cmd)
		return (NULL);
	if (is_built_in(cmd))
		return (ft_strdup(cmd));
	tmp = ft_strjoin("/", cmd);
	while (paths[++i])
	{
		maybe_path = ft_strjoin(paths[i], tmp);
		if (!access(maybe_path, F_OK))
		{
			free(tmp);
			return (maybe_path);
		}
		free(maybe_path);
	}
	return (ft_strdup(cmd));
}
