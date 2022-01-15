#include "../include/minishell.h"


void pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}


void voi (void)
{
	return ;
}

void pipes(char **env)
{
	char *huita[3] = {"/bin/cat", "-e", NULL};
	char *wcl[3] = {"/usr/bin/wc", "-l", NULL};
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execve(huita[0], huita, env);
	}
	else
	{
		close(fd[1]);
	}
	pid = fork();
	if (!pid)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		execve(wcl[0], wcl, env);
	}
	else
	{
		close(fd[0]);
	}
	int i = 0;
	while (i < 2)
	{
		wait(0);
		i++;
	}

}


t_cmd *lst_init(char **list)
{
	t_cmd *element;

	element = (t_cmd *)malloc(sizeof(t_cmd));
	element->next = NULL;
	element->back = NULL;
	element->cmd = list;
	return(element);
}

void lst_add(t_cmd **cmd, t_cmd *element)
{
	if(!(*cmd))
	{
		*cmd = element;
		return ;
	}
	element->back = *cmd;
	(*cmd)->next = element;
	(*cmd) = element;
}


void exec(t_cmd **cmd, char **env)
{
	t_cmd *tmp;
	pid_t pid;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	tmp = *cmd;
	pid = fork();
	if(!pid)
	{
		if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, ": ", 2);
			write(2, tmp->cmd[0], ft_strlen(tmp->cmd[0]));
			write(2, "\n", 1);
			exit(1);
		}
	}
	else 
		wait(0);
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

int main (int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *str;
	t_cmd *cmd;
	char **arguments;

	cmd = NULL;
	// char *from_D[5] = {"/usr/bin/say", "-v", "Milena", "чь", NULL};
	// char *from_D[3] = {"/usr/bin/say", "ту ту ту", NULL};

	// pipes(env);
	// return (0);
	while (1)
	{
		str = readline("AAAA БЛЯ ГДЕ Я?:>");
		if (!str || !ft_strncmp(str, "exit", 5))
			exit(0);
		if (!*str)
			continue ;
		if (str)
			add_history(str);
		arguments = ft_split(str, ' ');
		arguments[0] = get_path_commd(arguments[0], getenv("PATH"));
		lst_add(&cmd, lst_init(arguments));
		exec(&cmd, env);
		cmd = NULL;

	}
	free(str);
	return (0);
}
