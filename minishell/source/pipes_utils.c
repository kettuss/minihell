/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:39:06 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 22:42:50 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	to_close(int a, int b)
{
	close(a);
	close(b);
}

void	ft_error(char *cmd, char *error)
{
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}

int	exec_biultin_with_redirects(t_cmd *lst, t_env *env)
{
	int	land;
	int	p_a[2];

	p_a[0] = dup(0);
	p_a[1] = dup(1);
	check_stdin(lst);
	check_stdout(lst);
	land = exec_built_in(lst, env);
	dup2(p_a[0], 0);
	close(p_a[0]);
	dup2(p_a[1], 1);
	close(p_a[1]);
	return (land);
}

int	check_stdout(t_cmd *cmd)
{
	if (cmd->fd_out == -1)
		return (1);
	dup2(cmd->fd_out, 1);
	close(cmd->fd_out);
	return (0);
}

int	check_stdin(t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_in == -3)
		return (1);
	dup2(cmd->fd_in, 0);
	close(cmd->fd_in);
	return (0);
}
