#include "pipex.h"

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	child_process(char **av, char **envp, int *pipe_fd, int io_flag)
{
	int	fd_in;
	int	fd_out;

	if (io_flag == 0)
	{
		fd_in = file_open(av[1], io_flag);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			error_exit();
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit();
		close(fd_in);
		close_pipe(pipe_fd);
		execute_cmd(av[2], envp);
	}
	if (io_flag == 1)
	{
		fd_out = file_open(av[4], io_flag);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			error_exit();
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_exit();
		close(fd_out);
		close_pipe(pipe_fd);
		execute_cmd(av[3], envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		status;

	if (ac != 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd cmd outfile\n", 2), 1);
	if (pipe(pipe_fd) == -1)
		error_exit();
	pid1 = fork();
	if (pid1 == -1)
		error_exit();
	else if (pid1 == 0)
		child_process(av, envp, pipe_fd, 0);
	pid2 = fork();
	if (pid2 == -1)
		error_exit();
	else if (pid2 == 0)
		child_process(av, envp, pipe_fd, 1);
	close_pipe(pipe_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
