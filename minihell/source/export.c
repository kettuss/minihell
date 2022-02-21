#include "../include/minishell.h"

int check_duplicate_variable(t_env *env, char **str, char *original)
{
	while(env->back)
		env = env->back;
	while (env)
	{
		if (ft_strcmp(env->name, *str) == 0)
		{
			free(env->array);
			env->array = get_value(original);
			free_argv(str);
			return (1);
		}
		env = env->next;
	}
	free_argv(str);
	return (0);
}

void	add_variable(t_env *env, char *variable)
{
	while (env->next)
		env = env->next;
	lst_add_env(&env, lst_init_env(variable));
}

int ft_export(char **args, t_env **ev)
{
	t_env *env;
	int i = -1;
	while ((*ev)->back_order)
		*ev = (*ev)->back_order;
	env = *ev;
	if (!args || !*args)
	{
		while (env)
		{
			if (env->name && env->array)
				printf("declare -x %s=%s\n", env->name, env->array);
			else if (!env->array)
				printf("declare -x %s\n", env->name);
			env = env->next_order;
		}
	}
	else
	{
		while (args[++i])
		{
			if (!check_duplicate_variable(env, ft_split(args[i], '='), args[i]))
				add_variable(env, args[i]);
		}
		alpha_variables(env);
		while (env->back)
			env = env->back;
		*ev = env;
	}
	return (0);
}