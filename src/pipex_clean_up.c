#include "pipex.h"

void	close_all_fds(t_fds fds)
{
	close(fds.pipes[0]);
	close(fds.pipes[1]);
	close(fds.infile);
	close(fds.outfile);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	cmd_not_found(char *cmd)
{
	char	**command;

	command = ft_split(cmd, ' ');
	if (!command)
		exit(1);
	ft_putstr_fd(command[0], 2);
	free_arr(command);
	ft_putstr_fd(": Command not found\n", 2);
	exit(127);
}
