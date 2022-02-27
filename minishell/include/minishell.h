/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:17:56 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 21:51:20 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	g_exit;

typedef struct s_pipe
{
	int		p_a[2];
	int		p_b[2];
	int		flag;
	pid_t	pid;
	int		land;
}t_pipe;

typedef struct s_cmd
{
	char			**cmd;
	char			**redicts;
	int				fd_heredoc;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*back;
}t_cmd;

typedef struct s_env
{
	char			*name;
	char			*array;
	struct s_env	*next;
	struct s_env	*back;
	struct s_env	*next_order;
	struct s_env	*back_order;
}t_env;

int		pipes(t_cmd *lst, t_env **env);
t_cmd	*parce_input(char **input, t_env *env);
char	**ft_split_f_shell(char const *s, char c);
int		lentab(char **ms);
char	**argv_dup(char **ar);
t_cmd	*lst_init(char **list);
void	lst_add(t_cmd **cmd, t_cmd *element);
int		ft_strcmp(const char *s1, const char *s2);
int		redirect_right(char *file);
void	ft_redirect_register(t_cmd **cmd);
void	ctrl_wd(int signum);
void	cmd_c_sl(int signum);
void	cmd_c_fork(int signum);
void	sign(int signal);
char	*get_value(char *str);
char	*spc_trim(char *str);
char	*replace_pointer(char *new_str);
void	qoutes_trim(t_cmd **cmd);
t_env	*lst_init_env(char *str);
void	lst_add_env(t_env **lst, t_env *element);
t_env	*ajaraguju(char **env_v);
int		print_env(t_env *str);
int		echo(char **ogo);
char	*get_env(t_env *cmd, char *variable);
char	**env_chars(t_env *env);
int		pwd(t_env *env);
int		ft_cd(char *path, t_env *env);
int		ft_unset(t_env *env, char **variable);
void	free_env(t_env **env);
t_cmd	*free_cmd(t_cmd **cmd);

int		ft_get_nbr_symbols2(char const *s, char c, size_t *i, size_t *nb_strs);
int		ft_get_nbr_symbols(char const *s, char c, size_t *i, size_t *nb_strs);
size_t	ft_get_get_nbstr(char const *s, char c, size_t i, size_t nb_strs);
int		if_equals(char **next_str, size_t **next_str_len, char c, int i);
int		if_redirect(char **next_str, size_t **next_str_len, int i);
int		check_stdout(t_cmd *cmd);
int		check_stdin(t_cmd *cmd);
int		redirect_right_append(char *file);
int		redirect_left(char *file);

int		ft_export(char **args, t_env **ev);
void	alpha_variables(t_env *env);
int		valid_export_args(char *arg);
int		check_duplicate_variable(t_env *env, char **str, char *original);
char	*get_value_of_variable_from_env(t_env *env, char *variable);
void	dauther_process(t_cmd *lst, t_env **env, t_pipe pipes);
void	parent_process(t_cmd *lst, t_pipe *pipes);
void	to_close(int a, int b);
int		exec_biultin_with_redirects(t_cmd *lst, t_env *env);
void	ft_error(char *cmd, char *error);
void	red_right(t_cmd **cmd, int i);
void	red_right_app(t_cmd **cmd, int i);
int		red_left(t_cmd **cmd, int i);
void	red_left_dock(t_cmd **cmd);
void	ft_check_heredoc(t_cmd **cmd);
char	*path_cmp(char *cmd, char **paths);

int		is_built_in(char *cmd);
int		exec_built_in(t_cmd *cmd, t_env *env);
int		ft_exit(char **code);
void	free_argv(char **good_bye);
void	sign(int signal);
void	cmd_run(t_cmd **cmd);

#endif
