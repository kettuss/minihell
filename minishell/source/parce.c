/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:12 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/27 22:14:31 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_path_to_cmds(t_cmd **cmd, t_env *env)
{
	t_cmd	*tmp;
	char	**paths;
	char	*env_path;

	env_path = get_env(env, "PATH");
	if (!env_path)
		return ;
	paths = ft_split(env_path, ':');
	free(env_path);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	tmp = *cmd;
	while (*cmd)
	{
		env_path = (*cmd)->cmd[0];
		(*cmd)->cmd[0] = path_cmp((*cmd)->cmd[0], paths);
		free(env_path);
		*cmd = (*cmd)->next;
	}
	free_argv(paths);
	*cmd = tmp;
}

char	**argv_dup_without_position(char **str, int indx)
{
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	j = -1;
	new_arg = (char **)malloc(sizeof(char *) * lentab(str));
	new_arg[lentab(str)] = NULL;
	while (str[++j])
	{
		if (j == indx)
			continue ;
		new_arg[i] = ft_strdup(str[j]);
		i++;
	}
	return (new_arg);
}

char	**parce_bucks(char **input, char *temp, char **temp_mass, t_env *env)
{
	int	str;

	str = -1;
	while (input[++str])
	{
		temp = input[str];
		if (input && input[str] && !ft_strcmp(input[str], "$?"))
		{
			input[str] = ft_itoa(g_exit);
			free(temp);
		}
		else if (input && input[str] && input[str][0] == '$' && input[str][1])
		{
			input[str] = get_value_of_variable_from_env(env, input[str] + 1);
			if (!input[str])
			{
				temp_mass = input;
				input = argv_dup_without_position(input, str--);
				free_argv(temp_mass);
			}
			else
				free(temp);
		}
	}
	return (input);
}

t_cmd	*cmd_record_from_mass(char **input, int i)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (input[--i])
	{
		if (!ft_strcmp("|", input[i]))
		{
			lst_add(&cmd, lst_init(input + (i + 1)));
			i = lentab(input);
			while (ft_strcmp("|", input[--i]))
				free(input[i]);
			free(input[i]);
			input[i] = NULL;
		}
		if (i == 0)
		{
			lst_add(&cmd, lst_init(input));
			while (input[i])
				free(input[i++]);
			free(input);
			break ;
		}
	}
	return (cmd);
}

t_cmd	*parce_input(char **input, t_env *env)
{
	int		i;
	char	*temp;
	char	**temp_mass;
	t_cmd	*cmd;

	cmd = NULL;
	temp = NULL;
	temp_mass = NULL;
	input = parce_bucks(input, temp, temp_mass, env);
	i = lentab(input);
	if (!i)
		return (NULL);
	cmd = cmd_record_from_mass(input, i);
	cmd_run(&cmd);
	find_path_to_cmds(&cmd, env);
	return (cmd);
}
