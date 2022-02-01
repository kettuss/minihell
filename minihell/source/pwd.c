#include "../include/minishell.h"

char *get_env(t_env *cmd, char *variable)
{
	while(cmd->back)
		cmd = cmd->back;
	while(cmd)
	{
		if(!ft_strcmp(cmd->name, variable))
		{
			return(ft_strdup(cmd->array));
		}
		cmd = cmd->next;
	}
	return(NULL);

}

int pwd(t_env *env)
{
	char *var;

	while (env->back)
		env = env->back;
	var = get_env(env, "PWD");
	if (var)
	{
		ft_putstr_fd(var, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		printf("%s\n", getcwd(NULL, 0));
	}
	return (0);
}