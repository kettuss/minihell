/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:09 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/24 23:22:15 by kpeanuts         ###   ########.fr       */
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
	if (cmd->fd_in == -1)
		return (1);
	dup2(cmd->fd_in, 0);
	close(cmd->fd_in);
	return (0);
}

int exec_biultin_with_redirects(t_cmd *lst, t_env *env)
{
	int land;
	int p_a[2];
	
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

int	pipes(t_cmd *lst, t_env *env)
{
	int		p_a[2];
	int		p_b[2];
	int		flag;
	pid_t	pid;
	int		land;

	flag = 0;
	while (lst->back)
		lst = lst->back;
	if (is_built_in(lst->cmd[0]) && !lst->back && !lst->next)
		return (exec_biultin_with_redirects(lst, env));
	land = land_list(lst);
	while (lst)
	{
		if (lst->next)
		{
			if (!flag)
				pipe(p_a);
			else
				pipe(p_b);
		}
		pid = fork();
		if (!pid)
		{
			if (!lst->back && !lst->next)
			{
				check_stdin(lst);
				check_stdout(lst);
			}
			else if (!lst->back)
			{
				check_stdin(lst);
				if (check_stdout(lst))
					dup2(p_a[1], 1);
				close(p_a[0]);
				close(p_a[1]);
			}
			else if (lst->next && lst->back)
			{
				if (!flag)
				{
					if (check_stdout(lst))
						dup2(p_a[1], 1);
					if (check_stdin(lst))
						dup2(p_b[0], 0);
					close(p_a[0]);
					close(p_a[1]);
					close(p_b[0]);
				}
				else
				{
					if (check_stdout(lst))
						dup2(p_b[1], 1);
					if (check_stdin(lst))
						dup2(p_a[0], 0);
					close(p_a[0]);
					close(p_b[1]);
					close(p_b[0]);
				}
			}
			else if (!lst->next)
			{
				if (!flag)
				{
					check_stdout(lst);
					if (check_stdin(lst))
						dup2(p_b[0], 0);
					close(p_b[0]);
				}
				else
				{
					check_stdout(lst);
					if (check_stdin(lst))
						dup2(p_a[0], 0);
					close(p_a[0]);
				}
			}
			if (is_built_in(lst->cmd[0]))
				exit(exec_built_in(lst, env));
			if (execve(lst->cmd[0], lst->cmd, env_chars(env)) == -1)
			{
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, ": ", 2);
				write(2, lst->cmd[0], ft_strlen(lst->cmd[0]));
				write(2, "\n", 1);
				exit(1);
			}
		}
		else
		{
			if (lst->fd_in != -1)
				close(lst->fd_in);
			if (lst->fd_out != -1)
				close(lst->fd_out);
			if (!lst->next && !lst->back)
				;
			else if (!lst->back)
				close(p_a[1]);
			else if (lst->next && lst->back)
			{
				if (flag)
				{	
					close(p_b[1]);
					close(p_a[0]);
				}
				else
				{
					close(p_a[1]);
					close(p_b[0]);
				}
			}
			else if(!lst->next)
			{
				if(flag)
					close(p_a[0]);
				else
					close(p_b[0]);
			}
			if (!flag)
				flag = 1;
			else
				flag = 0;
			lst = lst->next;
		}
	}
	while (land--)
	{
		wait(0);
	}
	return (0);
}