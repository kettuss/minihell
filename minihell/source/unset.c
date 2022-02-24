#include "../include/minishell.h"

int ft_unset(t_env *env, char **variable)
{
	t_env *prev = NULL;
	t_env *temp;
	int i = -1;

	if (!variable)
		return (1);
	while (variable[++i])
	{
		while (env &&env->back)
			env = env->back;
		while (env)
		{
			if (!ft_strcmp(env->name, variable[i]))
			{
				if (env->next)
				{
					env->next->back = prev;
					temp = prev;
				}
				if (prev)
				{
					prev->next = env->next;
					temp = prev;
				}
				env->next = NULL;
				env->back = NULL;
				if (env->next_order)
					env->next_order->back_order = NULL;
				if (env->back_order)
					env->back_order->next_order = NULL;
				env->next_order = NULL;
				env->back_order = NULL;
				free(env->name);
				free(env->array);
				free(env);
				alpha_variables(temp);
				env = temp;
				break ;
			}
			prev = env;
			env = env->next;
		}
	}
	return (0);
}