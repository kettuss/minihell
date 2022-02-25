/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:10:51 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/25 20:55:37 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void pwd_patch(t_env *env, char *var, char *pwd_s)
{
	t_env *temp;
	if (!pwd_s)
	{
		ft_putstr_fd("error retrieving current directory: getcwd: cannot access \
		parent directories: No such file or directory\n", 2);
		return ;
	}
	while (env->back)
		env = env->back;
	temp = env;
	while(env)
	{
		if (!ft_strcmp(var, env->name))
		{
			free(env->array);
			env->array = ft_strdup(pwd_s);
			return ;
		}
		env = env->next;
	}
	env = temp;
	free(pwd_s);
}

int ft_cd(char *path, t_env *env)
{
	if (path && !ft_strcmp(path, "-"))
	{
		// free(path);
		path = get_env(env, "OLDPWD");
	}
	pwd_patch(env, "OLDPWD", get_env(env, "PWD"));
	if (!path)
	{
		path = get_env(env, "HOME");
		free(path);
	}
	else if (*path == '~')
	{
		path = ft_strjoin(get_env(env, "HOME"), (path + 1));
	}
	if (chdir(path) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (1);
	}
	pwd_patch(env, "PWD", getcwd(NULL, 0));
	return (0);
}