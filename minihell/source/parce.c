/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:54:12 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/21 19:54:13 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1[i] && !s2[i])
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void free_argv(char **good_bye)
{
	int i;

	i = -1;
	if (!good_bye || !*good_bye)
		return ;
	while (good_bye[++i])
		free(good_bye[i]);
	free(good_bye);
}

int	redirect_count(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
			count++;
	return (count * 2);
}

char	**record_redicts(char **argv)
{
	int		str;
	int		i;
	char	**temp;

	str = 0;
	i = 0;
	temp = (char **)malloc((redirect_count(argv) + 1) * sizeof(char *));
	while (argv[str])
	{
		if (!ft_strcmp(argv[str], ">>") || \
		!ft_strcmp(argv[str], ">") || \
		!ft_strcmp(argv[str], "<") || \
		!ft_strcmp(argv[str], "<<"))
		{
			temp[i] = ft_strdup(argv[str]);
			temp[i + 1] = ft_strdup(argv[str + 1]);
			i += 2;
			str += 2;
			continue ;
		}
		str++;
	}
	temp[i] = NULL;
	return (temp);
}

char	**rewrite_cmd(char **argv)
{
	int		i;
	int		str;
	char	**temp;

	i = 0;
	str = 0;
	temp = (char **)malloc(((lentab(argv) - redirect_count(argv)) + 1) * \
	sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
		{
			i += 2;
			continue ;
		}
		temp[str] = ft_strdup(argv[i]);
		str++;
		i++;
	}
	temp[str] = NULL;
	return (temp);
}


void	cmd_run(t_cmd **cmd)
{
	t_cmd		*temp;
	char		**ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->cmd;
		if (!ar || !*ar)
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		(*cmd)->redicts = record_redicts(ar);
		if (!(*cmd)->redicts)
			break ;
		(*cmd)->cmd = rewrite_cmd(ar);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}

char *path_cmp(char *cmd, char **paths)
{
	int i;
	char *tmp;
	char *maybe_path;

	i = -1;
	tmp = ft_strjoin("/", cmd);
	while (paths[++i])
	{
		maybe_path = ft_strjoin(paths[i], tmp);
		if (!access(maybe_path, F_OK))
		{
			free(tmp);
			return (maybe_path);
		}
		free(maybe_path);
	}
	return (ft_strdup(cmd));
}

void find_path_to_cmds(t_cmd **cmd)
{
	t_cmd *tmp;
	char **paths;
	char *env_path;

	env_path = getenv("PATH=");
	if (!env_path)
		return ;
	paths = ft_split(env_path + 5, ':');
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
	*cmd = tmp;
}

char **argv_dup_without_position(char **str, int indx)
{
	int i;
	int j;
	char **new_arg;

	i = 0;
	j = -1;
	new_arg = (char **)malloc(sizeof(char *) * lentab(str));
	new_arg[lentab(str) - 1] = NULL;
	while (str[++j])
	{
		if (j == indx)
			continue ;
		new_arg[i] = ft_strdup(str[j]);
		i++;
	}
	return (new_arg);
}

t_cmd *parce_input(char **input, t_env *env)
{
	t_cmd *cmd = NULL;
	int i;
	int str;
	char *temp;
	char **temp_mass;

	str = -1;
	while (input[++str])
	{
		if (input[str][0] == '$' && ft_strlen(input[str]) > 1)
		{
			temp = input[str];
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
	i = lentab(input);
	if (!i)
		return (cmd);
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
		else if (i == 0)
		{
			lst_add(&cmd, lst_init(input));
			while (input[i])
				free(input[i++]);
			free(input);
			break ;
		}
	}
	cmd_run(&cmd);
	find_path_to_cmds(&cmd);
	return (cmd);
}