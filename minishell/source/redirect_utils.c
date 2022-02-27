/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:10:38 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:11:05 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	red_right(t_cmd **cmd, int i)
{
	if ((*cmd)->fd_out != -1)
		close((*cmd)->fd_out);
	if ((*cmd)->fd_out)
		(*cmd)->fd_out = redirect_right((*cmd)->redicts[i + 1]);
}

void	red_right_app(t_cmd **cmd, int i)
{
	if ((*cmd)->fd_out != -1)
		close((*cmd)->fd_out);
	if ((*cmd)->fd_out)
		(*cmd)->fd_out = redirect_right_append((*cmd)->redicts[i + 1]);
}

int	red_left(t_cmd **cmd, int i)
{
	if ((*cmd)->fd_in != -1)
		close((*cmd)->fd_in);
	if ((*cmd)->fd_in)
		(*cmd)->fd_in = redirect_left((*cmd)->redicts[i + 1]);
	return ((*cmd)->fd_in);
}

void	red_left_dock(t_cmd **cmd)
{
	if ((*cmd)->fd_in != -1)
		close((*cmd)->fd_in);
	if ((*cmd)->fd_in)
		(*cmd)->fd_in = (*cmd)->fd_heredoc;
}
