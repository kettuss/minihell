#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char **cmd;
	char **redicts;
	int fd_in;
	int fd_out;
	struct s_cmd *next;
	struct s_cmd *back;
}t_cmd;


int pipes(t_cmd *lst, char **env);
t_cmd *parce_input(char **input);
char	**ft_split_f_shell(char const *s, char c);
int lentab(char **ms);
char **argv_dup(char **ar);
t_cmd *lst_init(char **list);
void lst_add(t_cmd **cmd, t_cmd *element);
int	ft_strcmp(const char *s1, const char *s2);
int redirect_right(char *file);
void ft_redirect_register(t_cmd **cmd);
/*
1)cmd[0] = "/bin/cat"
2)cmd[1] = "-e"
3)cmd[2] = "1"
4)cmd[3] = NULL

cmd = cmd->next;

1)cmd[0] = "usr/bin/wc"
2)cmd[1] = "-l"
3)cmd[2] = NULL
*/

void voi (void);



#endif
