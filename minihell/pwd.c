/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:47:04 by dadina            #+#    #+#             */
/*   Updated: 2022/01/30 19:47:15 by dadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char *pwd;

    pwd = ft_calloc(4096, 1);
    if (getcwd(pwd, 4096))
    {
        ft_putstr_fd(pwd, 1);
        free(pwd);
        write(1, "\n", 1);
        return(0);
    }
    else
    {
        print_errno();
        free(pwd);
        return(1);
    }
}
