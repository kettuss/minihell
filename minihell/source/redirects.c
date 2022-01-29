#include "minishell.h"

int redirect_right(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		return (0);
	return (fd);
}

int redirect_right_append(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_APPEND| O_CREAT, 0666);
	if (fd == -1)
		return (0);
	return (fd);
}

int redirect_left(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}

int ft_herdoc(char *stop)
{
	int fd[2];
	pid_t pid;
	char *str;
	void	*sgnl;
	sgnl = NULL;
	int	out;

	out = 0;
	pipe(fd);
	pid = fork();
	signal(SIGINT, ctrl_wd);
	signal(SIGQUIT, SIG_IGN);
	(sgnl = rl_getc_function);
	rl_getc_function = getc;
	if (!pid)
	{
		while(1)
		{
			str = readline("herdoc> ");
			if (!*str)
				continue ;
			if (g_exit == 130)
			{
				free(str);
				exit(130);
			}
			if(!str || ft_strcmp(str, stop) == 0)
				exit(0);
			ft_putstr_fd(str, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(str);
		}
	}
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

void ft_check_heredoc(t_cmd **cmd)
{
	t_cmd *temp;
	int i;

	i = -1;
	temp = *cmd;
	while (*cmd)
	{
		while((*cmd)->redicts[++i])
		{
			if(!ft_strcmp((*cmd)->redicts[i], "<<"))
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

void ft_redirect_register(t_cmd **cmd)
{
	t_cmd *tmp;
	int i;

	g_exit = 0;
	while((*cmd)->back)
	{
		*cmd = (*cmd)->back;
	}
	tmp = *cmd;
	ft_check_heredoc(cmd);
	if (g_exit == 130)
		return ;
	while(*cmd)
	{
		i = -1;
		while ((*cmd)->redicts[++i])
		{
			if (!ft_strcmp((*cmd)->redicts[i], ">"))
			{
				printf("pipska\n");
				if ((*cmd)->fd_out != -1)
					close((*cmd)->fd_out);
				(*cmd)->fd_out = redirect_right((*cmd)->redicts[i + 1]);
				//check yest li file
			}
			else if (!ft_strcmp((*cmd)->redicts[i], ">>"))
			{
				if ((*cmd)->fd_out != -1)
					close((*cmd)->fd_out);
				(*cmd)->fd_out = redirect_right_append((*cmd)->redicts[i + 1]);
				//check yest li file
			}
			else if (!ft_strcmp((*cmd)->redicts[i], "<"))
			{
				if ((*cmd)->fd_in != -1)
					close((*cmd)->fd_in);
				(*cmd)->fd_in = redirect_left((*cmd)->redicts[i + 1]);
				//check yest li file
			}
			else if (!ft_strcmp((*cmd)->redicts[i], "<<"))
			{
				if ((*cmd)->fd_in != -1)
					close((*cmd)->fd_in);
				(*cmd)->fd_in = (*cmd)->fd_heredoc;
				//check yest li file
			}
		}
		*cmd = (*cmd)->next;
	}
	*cmd = tmp;
}
