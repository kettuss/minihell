#include "../include/minishell.h"


int land_list(t_cmd *str)
{
	int i;
	
	i = 0;
	while(str)
	{	
		str = str->next;
		i++;
	}
	return(i);
}


int pipes(t_cmd *lst, char **env)
{
	int p_a[2];
	int p_b[2];
	int flag;
	pid_t pid;
	int land;

	flag = 0;
	while (lst->back)
		lst = lst->back;
	land = land_list(lst);
	while (lst)
	{
		if(lst->next)
		{
			if(!flag)
				pipe(p_a);
			else
				pipe(p_b);
		}
		pid = fork();
		if(!pid)
		{
			if (!lst->back && !lst->next)
				;
			else if(!lst->back)
			{
				dup2(p_a[1], 1);
				close(p_a[0]);
				close(p_a[1]);
			}
			else if(lst->next && lst->back)
			{
				if(!flag)
				{
					dup2(p_a[1], 1);
					dup2(p_b[0], 0);
					close(p_a[0]);
					close(p_a[1]);
					close(p_b[0]);
				}
				else
				{
					dup2(p_b[1], 1);
					dup2(p_a[0], 0);
					close(p_a[0]);
					close(p_b[1]);
					close(p_b[0]);
				}
			}
			else if(!lst->next)
			{
				if(!flag)
				{
					dup2(p_b[0], 0);
					close(p_b[0]);
				}
				else
				{
					dup2(p_a[0], 0);
					close(p_a[0]);
				}
			}
			if(execve(lst->cmd[0], lst->cmd, env) == -1)
			{
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, ": ", 2);
				write(2, lst->cmd[0], ft_strlen(lst->cmd[0]));
				write(2, "\n", 1);
				exit(1);
			}
		}
		else
		{
			if (!lst->next && !lst->back)
				;
			else if(!lst->back)
				close(p_a[1]);
			else if(lst->next && lst->back)
			{
				if(flag)
				{	
					close(p_b[1]);
					close(p_a[0]);
				}
				else
				{
					close(p_a[1]);
					close(p_b[0]);
				}
			}
			else if(!lst->next)
			{
				if(flag)
					close(p_a[0]);
				else
					close(p_b[0]);
			}
			if(!flag)
				flag = 1;
			else
				flag = 0;
			lst = lst->next;
		}
	}
	while(land--)
	{
		wait(0);
	}
	return(0);
}