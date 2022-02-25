#include "../include/minishell.h"

void	null_env(t_env **del)
{
	(*del)->next = NULL;
	(*del)->next_order = NULL;
	(*del)->back = NULL;
	(*del)->back_order = NULL;
}

void	cut_and_free_varias(t_env **env, t_env *temp)
{
	t_env	*del;

	del = *env;
	*env = (*env)->next;
	temp = del->back;
	if (!*env && !temp)
	{
		free_env(&del);
		return ;
	}
	if (temp)
		temp->next = *env;
	if (*env)
		(*env)->back = temp;
	else
		*env = temp;
	if (del->back_order)
		del->back_order->next_order = NULL;
	if (del->next_order)
		del->next_order->back_order = NULL;
	null_env(&del);
	free_env(&del);
}

void	value_delete(t_env **env, char *value)
{
	t_env	*temp;

	while ((*env)->back)
		*env = (*env)->back;
	temp = *env;
	while (*env)
	{
		if (!ft_strcmp((*env)->name, value))
		{
			cut_and_free_varias(env, temp);
			return ;
		}
		*env = (*env)->next;
	}
	if (!*env)
		*env = temp;
}

int	ft_unset(t_env *env, char **variable)
{
	int	str;

	str = 0;
	if (variable && variable[0])
	{
		while (variable[str])
			value_delete(&env, variable[str++]);
		while (env && env->back)
			env = env->back;
		alpha_variables(env);
	}
	return (0);
}