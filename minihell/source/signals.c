/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:23:15 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:48:18 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_wd(int signum)
{
	(void)signum;
	g_exit = 130;
}

void	cmd_c_sl(int signum)
{
	(void)signum;
	g_exit = 131;
	printf("Quit :3\n");
}

void	cmd_c_fork(int signum)
{
	(void)signum;
	g_exit = 130;
	write(1, "\n", 1);
}

void	sign(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	g_exit = 1;
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("c signal\n");
	rl_redisplay();
}
