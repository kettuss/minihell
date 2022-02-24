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

# define MAX 1
# define MIN 0

int g_exit;

typedef struct s_cmd
{
	char **cmd;
	char **redicts;
	int fd_heredoc;
	int fd_in;
	int fd_out;
	struct s_cmd *next;
	struct s_cmd *back;
}t_cmd;

typedef struct s_env
{
	char *name;
	char *array;
	// char symbol;
	struct s_env *next;
	struct s_env *back;
	struct s_env *next_order;
	struct s_env *back_order;
}t_env;

int pipes(t_cmd *lst, t_env *env);
t_cmd *parce_input(char **input, t_env *env);
char	**ft_split_f_shell(char const *s, char c);
int lentab(char **ms);
char **argv_dup(char **ar);
t_cmd *lst_init(char **list);
void lst_add(t_cmd **cmd, t_cmd *element);
int	ft_strcmp(const char *s1, const char *s2);
int redirect_right(char *file);
void ft_redirect_register(t_cmd **cmd);
void	ctrl_wd(int signum);
void	cmd_c_sl(int signum);
void	cmd_c_fork(int signum);
void sign(int signal);
char *get_value(char *str);
t_env *lst_init_env(char *str);
void lst_add_env(t_env **lst, t_env *element);
t_env *ajaraguju(char **env_v);
int print_env(t_env *str);
int echo(char **ogo);
char *get_env(t_env *cmd, char *variable);
char **env_chars(t_env *env);
int pwd(t_env *env);
int ft_cd(char *path, t_env *env);
int ft_unset(t_env *env, char **variable);

int	ft_get_nbr_symbols2(char const *s, char c, size_t *i, size_t *nb_strs);
int	ft_get_nbr_symbols(char const *s, char c, size_t *i, size_t *nb_strs);
size_t	ft_get_get_nbstr(char const *s, char c, size_t i, size_t nb_strs);
int	if_equals(char **next_str, size_t **next_str_len, char c, int i);
int	if_redirect(char **next_str, size_t **next_str_len, int i);
int	check_stdout(t_cmd *cmd);
int	check_stdin(t_cmd *cmd);

int ft_export(char **args, t_env **ev);
void	alpha_variables(t_env *env);
int check_duplicate_variable(t_env *env, char **str, char *original);
char *get_value_of_variable_from_env(t_env *env, char *variable);

int is_built_in(char *cmd);
int exec_built_in(t_cmd *cmd, t_env *env);

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
void free_argv(char **good_bye);
void voi (void);



#endif
