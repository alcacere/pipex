#include "pipex.h"

void	first_child(char **envp, char **av, int *pipe_fd)
{
	int	fd;

	fd = file_open(av[1], 0);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(av[2], envp);
}

void	second_child(char **envp, char **av, int *pipe_fd)
{
	int	fd;

	fd = file_open(av[3], 1);
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(av[3], envp);
}

int main (int ac, char **av, char **envp)
{
	int	pipe_fd[2];
	int pid1;
	int pid2;

	if (ac == 5)
	{
		if (pipe(pipe_fd) == -1)
			return (1);
		pid1 = fork();
		if (pid1 == -1)
			return (2);
		else if (pid1 == 0)
			first_child(envp, av, pipe_fd);
		pid2 = fork();
		if (pid2 == 0)
			second_child(envp, av, pipe_fd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (1);
}
