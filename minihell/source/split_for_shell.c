/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeanuts <kpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:29:05 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/27 20:49:23 by kpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_free(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}


int	ft_get_nbr_symbols2(char const *s, char c, size_t *i, size_t *nb_strs)
{
	if (s[(*i)] == c)
	{
		if ((s[(*i) + 1] != '|' && s[(*i) + 1] != '\'' && s[(*i) + 1] != '"'
				&& s[(*i) + 1] != '<' && s[(*i) + 1] != '>')
			&& (s[(*i) - 1] != '|' && s[(*i) - 1] != '\''
				&& s[(*i) - 1] != '"' && s[(*i) - 1] != '<'
				&& s[(*i) - 1] != '>'))
		{
			(*nb_strs)++;
			while (s[(*i)] && s[(*i)] == c)
				(*i)++;
			return (2);
		}
		else
			(*i)++;
	}
	if (s[(*i)] == '|' && s[(*i) + 1] != '|')
		(*nb_strs)++;
	return (0);
}

int	ft_get_nbr_symbols(char const *s, char c, size_t *i, size_t *nb_strs)
{
	if (s[(*i)] != c && s[(*i)] != '\"' && s[(*i)] != '\''
		&& s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>')
	{
		if (((*i) != 0) && s[(*i) - 1] != c)
			(*nb_strs)++;
		if ((*i) != 0 && (s[(*i) - 1] == c && (s[(*i) - 2] == '|'
					|| s[(*i) - 2] == '"' || s[(*i) - 2] == '\''
					|| s[(*i) - 2] == '<' || s[(*i) - 2] == '>')))
			(*nb_strs)++;
		while (s[(*i)] && s[(*i)] != c && s[(*i)] != '\"' && s[(*i)] != '\''
			&& s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>')
		{
			(*i)++;
			if (s[(*i)] == '=')
			{
				(*i)++;
				while (s[(*i)] && (s[(*i)] != '|'
						|| s[(*i)] != '<' || s[(*i)] != '>'
						|| s[(*i)] != c))
					(*i)++;
			}
		}
		return (2);
	}
	return (0);
}


size_t	ft_get_get_nbstr(char const *s, char c, size_t i, size_t nb_strs)
{
	while (s[i])
	{
		if (ft_get_nbr_symbols2(s, c, &i, &nb_strs) == 2
			|| ft_get_nbr_symbols(s, c, &i, &nb_strs) == 2)
			continue ;
		if (s[i] == 34 || s[i] == 39)
		{
			nb_strs++;
			if (s[i++] == 34)
				while (s[i++] != 34)
					;
			else
				while (s[i++] != 39)
					;
			continue ;
		}
		if (s[i] == '<' || s[i] == '>')
		{
			nb_strs++;
			if (s[i + 1] == '<' || s[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (nb_strs);
}


static	size_t	ft_get_nb_strs(char const *s, char c)
{
	size_t	i;
	size_t	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] != c && s[i] != '\"' && s[i] != '\''
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
		nb_strs++;
	return (ft_get_get_nbstr(s, c, i, nb_strs));
}

int	if_equals(char **next_str, size_t **next_str_len, char c, int i)
{
	(void)c;
	if ((*next_str)[i] == '=')
	{
		(*(*next_str_len))++;
		i++;
		while ((*next_str)[i] && ((*next_str)[i] != '|'
			|| (*next_str)[i] == '<' || (*next_str)[i] == '<'
			|| (*next_str)[i] == ' '))
		{
			(*(*next_str_len))++;
			i++;
		}
		return(2);
	}
	return (0);
}

int	if_redirect(char **next_str, size_t **next_str_len, char c, int i)
{
	(void)c;
	if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
	{
		i++;
		(*(*next_str_len))++;
		if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
		{
			i++;
			(*(*next_str_len))++;
		}
		return (2);
	}
	if ((*next_str)[i] == '|' && (*next_str)[i + 1] != '|')
	{
		i++;
		(*(*next_str_len))++;
		return (2);
	}
	if ((*next_str)[i] == '|' && (*next_str)[i + 1] == '|')
	{
		i += 2;
		*(*next_str_len) += 2;
		return (2);
	}
	return (0);
}

int	if_quotes(char **next_str, size_t **next_str_len, char c, int i)
{
	(void)c;
	if ((*next_str)[i] == '\"')
	{
		i++;
		while ((*next_str)[i] != '\"')
		{
			i++;
			(*(*next_str_len))++;
		}
		i++;
		(*(*next_str_len)) += 2;
		return (2);
	}
	if ((*next_str)[i] == '\'')
	{
		i++;
		while ((*next_str)[i] != '\'')
		{
			i++;
			(*(*next_str_len))++;
		}
		(*(*next_str_len)) += 2;
		i++;
		return (2);
	}
	return (0);
}


static void	ft_get_next_str(char **next_str, size_t *next_str_len, char c)
{
	size_t	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		if (if_quotes(next_str, &next_str_len, c, i) == 2
			|| if_redirect(next_str, &next_str_len, c, i) == 2
			|| if_equals(next_str, &next_str_len, c, i) == 2)
			return ;
		(*next_str_len)++;
		i++;
		if ((*next_str)[i] == '|' || (*next_str)[i] == '\"'
		|| (*next_str)[i] == '\'' || (*next_str)[i] == '<'
		|| (*next_str)[i] == '>')
			return ;
	}
}

char	**ft_split_f_shell(char const *s, char c)
{
	size_t	nb_strs;
	size_t	len;
	char	**buf;
	char	*next_str;
	size_t		i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	buf = (char **)malloc(sizeof(char *) * ((nb_strs) + 1));
	len = 0;
	if (!buf)
		return (NULL);
	i = -1;
	next_str = (char *)s;
	while (++i < nb_strs)
	{
		ft_get_next_str(&next_str, &len, c);
		buf[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!buf[i])
			return (ft_split_free(buf));
		ft_strlcpy(buf[i], next_str, (len + 1));
	}
	buf[i] = NULL;
	return (buf);
}
