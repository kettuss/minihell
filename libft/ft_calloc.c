/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:12:37 by kpeanuts          #+#    #+#             */
/*   Updated: 2022/02/26 23:12:38 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*prt;

	prt = (char *)malloc(count * size);
	if (!prt)
		return (NULL);
	ft_memset (prt, 0, (count * size));
	return (prt);
}
