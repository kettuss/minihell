#include "../include/minishell.h"

char *get_value_of_variable_from_env(t_env *env, char *variable)
{
	while (env->back)
		env = env->back;
	while (env)
	{
		if (ft_strcmp(env->name, variable) == 0)
		{
			if (env->array)
				return (ft_strdup(env->array));
			break;
		}
		env = env->next;
	}
	return (NULL);
}

int lenenv(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char **env_chars(t_env *env)
{
	char **env_chars;
	char *temp;
	int i;

	env_chars = (char **)malloc(sizeof(char *) * (lenenv(env) + 1));
	env_chars[lenenv(env)] = NULL;
	i = 0;
	while (env)
	{
		env_chars[i] = ft_strdup(env->name);
		temp = env_chars[i];
		if (env->array && *env->array)
		{
			env_chars[i] = ft_strjoin(env_chars[i], "=");
			free(temp);
			temp = env_chars[i];
			env_chars[i] = ft_strjoin(env_chars[i], env->array);
			free(temp);
		}
		else
			free(temp);
		env = env->next;
		i++;
	}
	return (env_chars);
}

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
	alpha_variables(tyt);
	return(tyt);
}
