/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:23 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 22:02:16 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_usd(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i + 1] == '$' && ft_strlen(str + (i + 2)) > 0)
		return (get_value_of_variable_from_env(env, str + (i + 2)));
	if (!str[i + 1])
		return (NULL);
	return (ft_strdup(str + (i + 1)));
}

int	check_duplicate_variable(t_env *env, char **str, char *original)
{
	while (env->back)
		env = env->back;
	while (env)
	{
		if (ft_strcmp(env->name, *str) == 0)
		{
			if (env->array)
				free(env->array);
			env->array = check_usd(original, env);
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

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->name && env->array)
			printf("declare -x %s=\"%s\"\n", env->name, env->array);
		else if (!env->array)
			printf("declare -x %s\n", env->name);
		env = env->next_order;
	}
}

int	ft_export(char **args, t_env **ev)
{
	t_env	*env;
	int		i;

	i = -1;
	while (*ev && (*ev)->back_order)
		*ev = (*ev)->back_order;
	env = *ev;
	if (!args || !*args)
		print_export(env);
	else
	{
		while (args[++i])
		{
			if (!valid_export_args(args[i]))
				continue ;
			if (!check_duplicate_variable(env, \
			ft_split(args[i], '='), args[i]))
				add_variable(env, args[i]);
		}
		alpha_variables(env);
		while (env->back)
			env = env->back;
		*ev = env;
	}
	return (0);
}
