/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:53:54 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/24 22:49:41 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*get_maxmin_variable(t_env *variable, _Bool min_max)
{
	t_env	*temp;
	t_env	*min;
	int		difference;

	temp = variable;
	min = variable;
	difference = 0;
	while (temp && temp->back)
		temp = temp->back;
	while (temp)
	{
		if (min_max == MAX && \
		ft_strcmp(min->name, temp->name) < difference)
			min = temp;
		if (min_max == MIN && \
		ft_strcmp(min->name, temp->name) > difference)
			min = temp;
		temp = temp->next;
	}
	return (min);
}

t_env	*get_up_neighbour(t_env *el)
{
	t_env	*start;
	t_env	*tmp;

	start = el;
	tmp = get_maxmin_variable(el, MAX);
	if (tmp == el)
		return (NULL);
	while (start->back)
		start = start->back;
	while (start)
	{
		if (ft_strcmp(start->name, tmp->name) < 0 \
		&& ft_strcmp(start->name, el->name) > 0)
			tmp = start;
		start = start->next;
	}
	return (tmp);
}

void	alpha_variables(t_env *env)
{
	t_env	*min;
	t_env	*max;

	if (!env || (!env->next && !env->back))
		return ;
	while (env->back)
		env = env->back;
	min = get_maxmin_variable(env, MIN);
	max = get_maxmin_variable(env, MAX);
	while (min != max)
	{
		min->next_order = get_up_neighbour(min);
		if (min->next_order)
			min->next_order->back_order = min;
		min = min->next_order;
	}
}
