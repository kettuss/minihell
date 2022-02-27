/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:09 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 22:39:40 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	land_list(t_cmd *str)
{
	int	i;

	i = 0;
	while (str)
	{
		str = str->next;
		i++;
	}
	return (i);
}

static void	the_pids_waiting(int len)
{
	int	out;

	while (len--)
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_exit = WEXITSTATUS(out);
	}
}

void	init_pipe_structure(t_cmd *cmd, t_pipe *pipe)
{
	pipe->flag = 0;
	pipe->land = land_list(cmd);
}

int	pipes(t_cmd *lst, t_env **env)
{
	t_pipe	pipes;

	init_pipe_structure(lst, &pipes);
	if (is_built_in(lst->cmd[0]) && !lst->back && !lst->next)
		return (exec_biultin_with_redirects(lst, *env));
	while (lst)
	{
		if (lst->next)
		{
			if (!pipes.flag)
				pipe(pipes.p_a);
			else
				pipe(pipes.p_b);
		}
		pipes.pid = fork();
		if (!pipes.pid)
			dauther_process(lst, env, pipes);
		else
		{
			parent_process(lst, &pipes);
			lst = lst->next;
		}
	}
	the_pids_waiting(pipes.land);
	return (g_exit);
}
