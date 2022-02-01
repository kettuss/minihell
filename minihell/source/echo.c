#include "../include/minishell.h"

int flag_n(char *str)
{
	int i;

	i = 0;
	if(str[0] != '-')
		return(1);
	while(str[++i])
	{
		if(str[i] != 'n')
			return (1);
	}
	return(0);
}
int echo(char **ogo)
{
	int ogogo;
	int slash_n;

	ogogo = 0;
	slash_n = 0;
	while(ogo[ogogo] != NULL && !flag_n(ogo[ogogo]))
	{
		slash_n = 1;
		ogogo++;
	}
	while(ogo[ogogo])
	{
		ft_putstr_fd(ogo[ogogo], 1);
		if(ogo[ogogo + 1] != NULL)
			ft_putstr_fd(" ", 1);
		ogogo++;
	}
	if(slash_n == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
