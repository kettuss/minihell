/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:26 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 21:36:56 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_value_of_variable_from_env(t_env *env, char *variable)
{
	while (env->back)
		env = env->back;
	while (env)
	{
		if (ft_strcmp(env->name, variable) == 0)
		{
			if (env->array)
				return (ft_strdup(env->array));
			break ;
		}
		env = env->next;
	}
	return (NULL);
}

int	lenenv(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_chars(t_env *env)
{
	char	**env_chars;
	char	*temp;
	int		i;

	env_chars = (char **)malloc(sizeof(char *) * (lenenv(env) + 1));
	env_chars[lenenv(env)] = NULL;
	i = 0;
	while (env)
	{
		env_chars[i] = ft_strdup(env->name);
		temp = env_chars[i];
		if (env->array && *env->array)
		{
			env_chars[i] = ft_strjoin(env_chars[i], "=");
			free(temp);
			temp = env_chars[i];
			env_chars[i] = ft_strjoin(env_chars[i], env->array);
			free(temp);
		}
		else
			free(temp);
		env = env->next;
		i++;
	}
	return (env_chars);
}

int	print_env(t_env *str)
{
	while (str->back)
	{
		str = str->back;
	}
	while (str)
	{
		if (str->array)
		{
			ft_putstr_fd(str->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(str->array, 1);
			ft_putstr_fd("\n", 1);
		}
		str = str->next;
	}
	return (0);
}

char	*get_value(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (ft_strdup(str + (i + 1)));
	}
	return (NULL);
}
