/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:49:02 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 00:53:51 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_argvs(char **ar)
{
	int	str;

	str = 0;
	while (ar[str])
		str++;
	return (str);
}

int	is_numbers_to_string(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

int	is_numbers_to_arguments(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_numbers_to_string(str[i]))
			return (0);
	}
	return (1);
}

static int	ft_exit_util(char **code)
{
	if (is_numbers_to_string(*code))
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("exit\nexit: ", 2);
		ft_putstr_fd(*code, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	return (0);
}

int	ft_exit(char **code)
{
	if (!code || !*code)
		exit(0);
	if (len_argvs(code) == 1)
	{
		if (!is_numbers_to_string(*code))
		{
			ft_putstr_fd("exit\nexit: ", 2);
			ft_putstr_fd(*code, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(ft_atoi(*code));
	}
	else
		return (ft_exit_util(code));
	return (0);
}
