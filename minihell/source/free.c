/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:13:06 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 19:13:25 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env && (*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->name);
		free(temp->array);
		free(temp);
	}
}

t_cmd	*free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	while (*cmd && (*cmd)->back)
		*cmd = (*cmd)->back;
	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		free_argv(temp->cmd);
		free_argv(temp->redicts);
		free(temp);
	}	
	return (NULL);
}
