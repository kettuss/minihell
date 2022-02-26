/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:11:40 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:11:46 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_execute(char *stop, int *fd)
{
	char	*str;

	while (1)
	{
		str = readline("herdoc> ");
		if (!*str)
			continue ;
		if (g_exit == 130)
		{
			free(str);
			exit(130);
		}
		if (!str || ft_strcmp(str, stop) == 0)
			exit(0);
		ft_putstr_fd(str, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(str);
	}
}

int	ft_herdoc(char *stop)
{
	int		fd[2];
	pid_t	pid;
	void	*sgnl;
	int		out;

	sgnl = NULL;
	out = 0;
	pipe(fd);
	pid = fork();
	signal(SIGINT, ctrl_wd);
	signal(SIGQUIT, SIG_IGN);
	(sgnl = rl_getc_function);
	rl_getc_function = getc;
	if (!pid)
		heredoc_execute(stop, fd);
	else
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_exit = WEXITSTATUS(out);
		close(fd[1]);
	}
	(rl_getc_function = sgnl);
	signal(SIGINT, cmd_c_fork);
	return (fd[0]);
}

void	ft_check_heredoc(t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;

	i = -1;
	temp = *cmd;
	while (*cmd)
	{
		while ((*cmd)->redicts && (*cmd)->redicts[++i])
		{
			if (!ft_strcmp((*cmd)->redicts[i], "<<"))
			{
				if ((*cmd)->fd_heredoc != -1)
					close((*cmd)->fd_heredoc);
				(*cmd)->fd_heredoc = ft_herdoc((*cmd)->redicts[i + 1]);
				if (g_exit == 130)
				{
					close((*cmd)->fd_heredoc);
					return ;
				}
			}
		}
		i = -1;
		(*cmd) = (*cmd)->next;
	}
	*cmd = temp;
}

void	ft_redirect_register_utils(t_cmd **cmd)
{
	int	i;

	i = -1;
	while ((*cmd)->redicts && (*cmd)->redicts[++i])
	{
		if (!ft_strcmp((*cmd)->redicts[i], ">"))
			red_right(cmd, i);
		else if (!ft_strcmp((*cmd)->redicts[i], ">>"))
			red_right_app(cmd, i);
		else if (!ft_strcmp((*cmd)->redicts[i], "<"))
		{
			if (red_left(cmd, i) == -3)
				break ;
		}
		else if (!ft_strcmp((*cmd)->redicts[i], "<<"))
			red_left_dock(cmd);
	}
}

void	ft_redirect_register(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	ft_check_heredoc(cmd);
	if (g_exit == 130)
		return ;
	while (*cmd)
	{
		ft_redirect_register_utils(cmd);
		*cmd = (*cmd)->next;
	}
	*cmd = tmp;
}
