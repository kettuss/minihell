/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:17 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/25 23:11:14 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

void	voi(void)
{
	return ;
}

int	lentab(char **ms)
{
	int	i;

	i = -1;
	while (ms[++i])
		;
	return (i);
}

char	**argv_dup(char **ar)
{
	int		i;
	char	**copy;

	i = -1;
	copy = (char **)malloc(sizeof(char *) * (lentab(ar) + 1));
	copy[lentab(ar)] = NULL;
	while (ar[++i])
		copy[i] = ft_strdup(ar[i]);
	return (copy);
}

t_cmd	*lst_init(char **list)
{
	t_cmd	*element;

	element = (t_cmd *)malloc(sizeof(t_cmd));
	element->next = NULL;
	element->back = NULL;
	element->redicts = NULL;
	element->fd_heredoc = -1;
	element->fd_in = -1;
	element->fd_out = -1;
	element->cmd = argv_dup(list);
	return (element);
}

void	lst_add(t_cmd **cmd, t_cmd *element)
{
	if (!(*cmd))
	{
		*cmd = element;
		return ;
	}
	element->next = *cmd;
	(*cmd)->back = element;
	(*cmd) = element;
}


void	exec(t_cmd **cmd, t_env **env)
{
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	while ((*env)->back)
		*env = (*env)->back;
	ft_redirect_register(cmd);
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
		if ((fd = open(ft_strjoin(paths[i], ft_strjoin("/", cmd)), O_RDONLY)) != -1)
		{
			close(fd);
			return (ft_strjoin(paths[i], ft_strjoin("/", cmd)));
		}
	}
	return (cmd);
}

void	test(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->back)
		cmd = cmd->back;
	while (cmd)
	{
		i = -1;
		while (cmd->cmd[++i])
		{
			printf("%s\n", cmd->cmd[i]);
		}
		i = -1;
		while (cmd->redicts[++i])
			printf("       %s\n", cmd->redicts[i]);
		cmd = cmd->next;
		printf("{}{}{}{}{}{}{}{}\n");
	}
}

void	ctrl_wd(int signum)
{
	(void)signum;
	g_exit = 130;
}

void	cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void	cmd_c_fork(int signum)
{
	(void)signum;
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



int	main(int argc, char **argv, char **ev)
{
	(void)argc;
	(void)argv;
	char	*str;
	char	**env;
	t_cmd	*cmd;
	t_env	*evnironment;

	cmd = NULL;
	str = NULL;
	env = argv_dup(ev);
	evnironment = ajaraguju(env);
	// ft_unset(evnironment, ft_split("Apple_PubSub_Socket_Render COLORTERM CPPFLAGS GIT_ASKPASS HOME HOMEBREW_CACHE HOMEBREW_TEMP LANG LDFLAGS LESS LOGNAME LSCOLORS OLDPWD ORIGINAL_XDG_CURRENT_DESKTOP PAGER PATH PWD SHELL SHLVL SSH_AUTH_SOCK TERM TERM_PROGRAM TERM_PROGRAM_VERSION TMPDIR USER VSCODE_GIT_ASKPASS_EXTRA_ARGS VSCODE_GIT_ASKPASS_MAIN VSCODE_GIT_ASKPASS_NODE VSCODE_GIT_IPC_HANDLE XPC_FLAGS XPC_SERVICE_NAME ZSH __CF_USER_TEXT_ENCODING", ' '));
	// ft_export(NULL, &evnironment);
	// ft_cd("-", &evnironment);
	// ft_export(NULL, &evnironment);
	// ft_cd("~", &evnironment);
	// ft_export(NULL, &evnironment);

	// char *from_D[5] = {"/usr/bin/say", "-v", "Milena", "чь", NULL};
	// char *from_D[3] = {"/usr/bin/say", "ту ту ту", NULL};

	// pipes(env);
	// return (0);
	g_exit = 0;
	while (1)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell> ");
		signal(SIGINT, cmd_c_fork);
		signal(SIGQUIT, cmd_c_sl);
		// str = ft_strdup("> 3 cat -e 4 | < f1 wc -l > f2 | pwd | ls -la");
		// str = ft_strdup("<4 >> 1 << 123 >> 1 >2 cat -e 4 <w <<w >> 2 > r");
		// str = ft_strdup("say -v Yuri \"Айгуль, че как? Попу мыл? good\"");
		// str = ft_strdup("$a | wc -l");
		if (!str || !ft_strncmp(str, "exit", 5))
		{	
			write(1, "exit\n", 5);
			exit(0);
		}
		if (!*str)
			continue ;
		if (str)
			add_history(str);
		cmd = parce_input(ft_split_f_shell(str, ' '), evnironment);
		g_exit = 0;
		if (!cmd)
			continue ;
		// test(cmd);
		// exit(0);
		exec(&cmd, &evnironment);
		cmd = free_cmd(&cmd);
		// break ;
	}
	free_argv(env);
	free(str);
	return (0);
}
