#include "pipex.h"

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}
