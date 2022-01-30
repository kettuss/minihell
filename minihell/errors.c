/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:42:50 by dadina            #+#    #+#             */
/*   Updated: 2022/01/30 21:42:56 by dadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_errno(void)
{
    ft_putstr_fd(strerror(errno), 2);
    write(2, "\n", 2);
    return (1);
}
