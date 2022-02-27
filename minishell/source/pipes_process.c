/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:39:21 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 22:39:22 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent_process(t_cmd *lst, t_pipe *pipes)
{
	if (lst->fd_in != -1)
		close(lst->fd_in);
	if (lst->fd_out != -1 && lst->fd_out != -3)
		close(lst->fd_out);
	if (!(!lst->next && !lst->back) && !lst->back)
		close(pipes->p_a[1]);
	else if (!(!lst->next && !lst->back) && lst->next && lst->back)
	{
		if (pipes->flag)
			to_close(pipes->p_b[1], pipes->p_a[0]);
		else
			to_close(pipes->p_a[1], pipes->p_b[0]);
	}
	else if (!(!lst->next && !lst->back) && !lst->next)
	{
		if (pipes->flag)
			close(pipes->p_a[0]);
		else
			close(pipes->p_b[0]);
	}
	if (!pipes->flag)
		pipes->flag = 1;
	else
		pipes->flag = 0;
}

void	begin_cmd(t_cmd *lst, t_pipe pipes)
{
	check_stdin(lst);
	if (check_stdout(lst))
		dup2(pipes.p_a[1], 1);
	close(pipes.p_a[0]);
	close(pipes.p_a[1]);
}

void	mid_cmd(t_cmd *lst, t_pipe pipes)
{
	if (!pipes.flag)
	{
		if (check_stdout(lst))
			dup2(pipes.p_a[1], 1);
		if (check_stdin(lst))
			dup2(pipes.p_b[0], 0);
		close(pipes.p_a[0]);
		close(pipes.p_a[1]);
		close(pipes.p_b[0]);
	}
	else
	{
		if (check_stdout(lst))
			dup2(pipes.p_b[1], 1);
		if (check_stdin(lst))
			dup2(pipes.p_a[0], 0);
		close(pipes.p_a[0]);
		close(pipes.p_b[1]);
		close(pipes.p_b[0]);
	}
}

void	last_cmd(t_cmd *lst, t_pipe pipes)
{
	if (!pipes.flag)
	{
		check_stdout(lst);
		if (check_stdin(lst))
			dup2(pipes.p_b[0], 0);
		close(pipes.p_b[0]);
	}
	else
	{
		check_stdout(lst);
		if (check_stdin(lst))
			dup2(pipes.p_a[0], 0);
		close(pipes.p_a[0]);
	}
}

void	dauther_process(t_cmd *lst, t_env **env, t_pipe pipes)
{
	if (!lst->back && !lst->next)
	{
		check_stdin(lst);
		check_stdout(lst);
	}
	else if (!lst->back)
		begin_cmd(lst, pipes);
	else if (lst->next && lst->back)
		mid_cmd(lst, pipes);
	else if (!lst->next)
		last_cmd(lst, pipes);
	if (lst->fd_in == -3 || lst->fd_out == -3)
		exit(1);
	if (is_built_in(lst->cmd[0]))
		exit(exec_built_in(lst, *env));
	if (execve(lst->cmd[0], lst->cmd, env_chars(*env)) == -1)
		ft_error(lst->cmd[0], strerror(errno));
}
