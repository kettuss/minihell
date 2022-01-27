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
	struct s_cmd *next;
	struct s_cmd *back;
}t_cmd;


int pipes(t_cmd *lst, char **env);
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
