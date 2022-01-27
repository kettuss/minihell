#include "minishell.h"

int redirect_right(char *file)
{
	int fd;

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT);
	if (fd == -1)
		return (1);
	return (0);
}

int  main(void)
{
	redirect_right("Айгуль моя красавица");
}
