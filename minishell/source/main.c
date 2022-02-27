/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:17 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 20:01:09 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

void	exec(t_cmd **cmd, t_env **env)
{
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	while ((*env)->back)
		*env = (*env)->back;
	g_exit = 0;
	ft_redirect_register(cmd);
	qoutes_trim(cmd);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	if (g_exit == 130)
		return ;
	g_exit = pipes(*cmd, env);
}

char	*get_path_commd(char *cmd, char *path)
{
	char	**paths;
	int		fd;
	int		i;

	i = -1;
	path += 5;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		fd = open(ft_strjoin(paths[i], ft_strjoin("/", cmd)), O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (ft_strjoin(paths[i], ft_strjoin("/", cmd)));
		}
	}
	return (cmd);
}

t_env	*ajaraguju_start(char **ev)
{
	t_env	*res;
	char	**env;

	env = argv_dup(ev);
	res = ajaraguju(env);
	free_argv(env);
	return (res);
}

void	readline_loop(t_cmd *cmd, t_env *evnironment, char *str)
{
	while (1)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell> ");
		signal(SIGINT, cmd_c_fork);
		signal(SIGQUIT, cmd_c_sl);
		if (!str || !ft_strncmp(str, "exit", 5))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (!*str)
			continue ;
		if (str)
			add_history(str);
		str = replace_pointer(spc_trim(str));
		cmd = parce_input(ft_split_f_shell(str, ' '), evnironment);
		g_exit = 0;
		if (!cmd)
			continue ;
		exec(&cmd, &evnironment);
		free_cmd(&cmd);
		free(str);
	}
}

int	main(int argc, char **argv, char **ev)
{
	char	*str;
	t_cmd	*cmd;
	t_env	*evnironment;

	(void)argc;
	(void)argv;
	evnironment = ajaraguju_start(ev);
	cmd = NULL;
	str = NULL;
	g_exit = 0;
	readline_loop(cmd, evnironment, str);
	free_env(&evnironment);
	if (str)
		free(str);
	return (0);
}
