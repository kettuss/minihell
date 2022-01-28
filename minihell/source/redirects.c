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

void ft_redirect_register(t_cmd **cmd)
{
	t_cmd *tmp;
	int i;

	while((*cmd)->back)
	{
		*cmd = (*cmd)->back;
	}
	tmp = *cmd;
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
			// else if (!ft_strcmp((*cmd)->redicts[i], "<<"))
			// {
			// 	if ((*cmd)->fd_in != -1)
			// 		close((*cmd)->fd_in);
			// 	(*cmd)->fd_in = redirect_herdoc((*cmd)->redicts[i + 1]);
			// 	//check yest li file
			// }
		}
		*cmd = (*cmd)->next;
	}
	*cmd = tmp;
}
