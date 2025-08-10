#include "pipex.h"

void	close_all_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	close(fds[3]);
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
