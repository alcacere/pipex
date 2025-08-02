#include "pipex.h"

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	error_exit(void)
{
	perror("");
	exit(1);
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
	exit(127);
}
