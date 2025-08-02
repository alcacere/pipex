#include "pipex.h"

void	first_child(char **envp, char **av, int *pipe_fd)
{
	int	fd;

	fd = file_open(av[1], 0);
	if (fd == -1)
	{
		close_pipe(pipe_fd);
		error_exit();
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close_pipe(pipe_fd);
		close(fd);
		error_exit();
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close_pipe(pipe_fd);
		close(fd);
		error_exit();
	}
	close_pipe(pipe_fd);
	close(fd);
	execute_cmd(av[2], envp);
}

void	second_child(char **envp, char **av, int *pipe_fd)
{
	int	fd;

	fd = file_open(av[4], 1);
	if (fd == -1)
	{
		close_pipe(pipe_fd);
		error_exit();
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close_pipe(pipe_fd);
		close(fd);
		error_exit();
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close_pipe(pipe_fd);
		close(fd);
		error_exit();
	}
	close_pipe(pipe_fd);
	close(fd);
	execute_cmd(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (ac != 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd cmd outfile\n", 2), 1);
	if (pipe(pipe_fd) == -1)
		error_exit();
	pid1 = fork();
	if (pid1 == -1)
		error_exit();
	else if (pid1 == 0)
		first_child(envp, av, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		error_exit();
	if (pid2 == 0)
		second_child(envp, av, pipe_fd);
	close_pipe(pipe_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (status);
}
