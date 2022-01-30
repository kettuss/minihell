#include "../include/minishell.h"

int print_env(t_env *str)
{
	//write(1, &str, 10);
	while(str->back)
	{
		str = str->back;
	}
	while(str)
	{
		ft_putstr_fd(str->name, 1);
		if(str->array)
			ft_putstr_fd("=", 1);
		ft_putstr_fd(str->array, 1);
		ft_putstr_fd("\n", 1);
		str = str->next;
	}
	return(0);
}

char *get_value(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if(str[i] == '=')
			return(ft_strdup(str + (i + 1)));
	}
	return(NULL);
}

t_env *lst_init_env(char *str)
{
	t_env *tam;

	tam = (t_env *)malloc(sizeof(t_env));
	tam->back = NULL;
	tam->next = NULL;
	tam->next_order = NULL;
	tam->back_order = NULL;
	tam->name = *ft_split(str, '=');
	tam->array = get_value(str);
	return(tam);
}

void lst_add_env(t_env **lst, t_env *element)
{
	if(!*lst)
	{
		*lst = element;
		return ;
	}
	(*lst)->next = element;
	element->back = *lst;
	*lst = element;
}
t_env *ajaraguju(char **env_v)
{
	int i;
	t_env *tyt;

	i = -1;
	tyt = NULL;
	while(env_v[++i])
	{
		lst_add_env(&tyt, lst_init_env(env_v[i]));
	}
	return(tyt);
}