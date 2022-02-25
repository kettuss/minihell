#include "../include/minishell.h"

int is_built_in(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if(!ft_strcmp(cmd, "cd") \
	|| !ft_strcmp(cmd, "env") \
	|| !ft_strcmp(cmd, "export") 
	|| !ft_strcmp(cmd, "echo") \
	|| !ft_strcmp(cmd, "pwd") \
	|| !ft_strcmp(cmd, "unset") \
	|| !ft_strcmp(cmd, "exit"))
	{
		return(1);
	}
	return (0);
}

int exec_built_in(t_cmd *cmd, t_env *env)
{
	//cd, unset, env, export, echo, pwd, exit;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		return(ft_cd(cmd->cmd[1], env));
	else if(!ft_strcmp(cmd->cmd[0], "unset"))
		return(ft_unset(env, cmd->cmd + 1));
	else if(!ft_strcmp(cmd->cmd[0], "env"))
		return(print_env(env));
	else if(!ft_strcmp(cmd->cmd[0], "export"))
		return (ft_export(cmd->cmd + 1, &env));
	else if(!ft_strcmp(cmd->cmd[0], "echo"))
		return (echo(cmd->cmd + 1));
	else if(!ft_strcmp(cmd->cmd[0], "pwd"))
		return(pwd(env));
	else if(!ft_strcmp(cmd->cmd[0], "exit"))
		return (ft_exit(cmd->cmd + 1));
	return(0);
}