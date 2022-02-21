/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:17 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/21 19:54:18 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit;



void voi (void)
{
	return ;
}

int lentab(char **ms)
{
	int i = -1;
	while (ms[++i])
		;
	return (i);
}

char **argv_dup(char **ar)
{
	int i;
	char **copy;

	i = -1;
	copy = (char **)malloc(sizeof(char *) * (lentab(ar) + 1));
	copy[lentab(ar)] = NULL;
	while (ar[++i])
		copy[i] = ft_strdup(ar[i]);
	return (copy);
}

t_cmd *lst_init(char **list)
{
	t_cmd *element;

	element = (t_cmd *)malloc(sizeof(t_cmd));
	element->next = NULL;
	element->back = NULL;
	element->redicts = NULL;
	element->fd_heredoc = -1;
	element->fd_in = -1;
	element->fd_out = -1;
	element->cmd = argv_dup(list);
	return(element);
}

void lst_add(t_cmd **cmd, t_cmd *element)
{
	if(!(*cmd))
	{
		*cmd = element;
		return ;
	}
	element->next = *cmd;
	(*cmd)->back = element;
	(*cmd) = element;
}


void exec(t_cmd **cmd, t_env **env)
{
	// t_cmd *tmp;
	// pid_t pid;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	while ((*env)->back)
		*env = (*env)->back;
	ft_redirect_register(cmd);
	if (g_exit == 130)
		return ;
	pipes(*cmd, *env);
	return ;
	// tmp = *cmd;
	// if (tmp->redicts != NULL)
	// {
	// 	tmp->fd_out = redirect_right(tmp->redicts[1]);
	// }
	// pid = fork();
	// if(!pid)
	// {
	// 	if (tmp->redicts != NULL)
	// 	{
	// 		dup2(tmp->fd_out, 1);
	// 		close(tmp->fd_out);
	// 	}
	// 	if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
	// 	{
	// 		write(2, strerror(errno), ft_strlen(strerror(errno)));
	// 		write(2, ": ", 2);
	// 		write(2, tmp->cmd[0], ft_strlen(tmp->cmd[0]));
	// 		write(2, "\n", 1);
	// 		exit(1);
	// 	}
	// }
	// else 
	// 	wait(0);
}

char *get_path_commd(char *cmd, char *path)
{
	char **paths;
	int fd;
	int i;

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

void test(t_cmd *cmd)
{
	int i = -1;
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

void sign(int signal)
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

int main (int argc, char **argv, char **ev)
{
	(void)argc;
	(void)argv;
	char *str;
	char **env;
	t_cmd *cmd;
	t_env *evnironment;

	cmd = NULL;
	str = NULL;
	env = argv_dup(ev);
	evnironment = ajaraguju(env);
	ft_export(ft_split("a=/bin/cat", ' '), &evnironment);
	ft_export(NULL, &evnironment);

	// char *from_D[5] = {"/usr/bin/say", "-v", "Milena", "чь", NULL};
	// char *from_D[3] = {"/usr/bin/say", "ту ту ту", NULL};

	// pipes(env);
	// return (0);
	g_exit = 0;
	while (1)
	{
		signal(SIGINT, sign);
		signal(SIGQUIT, SIG_IGN);
		str = readline("AAA БЛЯ ГДЕ Я?> ");
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
		// if (str)
		// 	add_history(str);
		cmd = parce_input(ft_split_f_shell(str, ' '), evnironment);
		if (!cmd)
			continue ;
		// test(cmd);
		// exit(0);
		if(!ft_strncmp(str, "echo", 4))
		{
			echo(cmd->cmd + 1);
			continue ;	
		}
		if(!ft_strncmp(str, "pwd", 3))
		{
			pwd(evnironment);
			continue ;	
		}
		exec(&cmd, &evnironment);
		cmd = NULL;

		break ;
	}
	free_argv(env);
	free(str);
	return (0);
	
}
