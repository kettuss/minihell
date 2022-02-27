/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_add_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:53:16 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 19:58:08 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*lst_init_env(char *str)
{
	t_env	*tam;
	char	**temp;

	tam = (t_env *)malloc(sizeof(t_env));
	tam->back = NULL;
	tam->next = NULL;
	tam->next_order = NULL;
	tam->back_order = NULL;
	temp = ft_split(str, '=');
	tam->name = ft_strdup(*temp);
	free_argv(temp);
	tam->array = get_value(str);
	return (tam);
}

void	lst_add_env(t_env **lst, t_env *element)
{
	if (!*lst)
	{
		*lst = element;
		return ;
	}
	(*lst)->next = element;
	element->back = *lst;
	*lst = element;
}

t_env	*ajaraguju(char **env_v)
{
	int		i;
	t_env	*tyt;

	i = -1;
	tyt = NULL;
	while (env_v[++i])
	{
		lst_add_env(&tyt, lst_init_env(env_v[i]));
	}
	alpha_variables(tyt);
	return (tyt);
}
