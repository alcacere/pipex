#include "pipex.h"

void	first_child(t_pipex cmd_struct, int *pipe_fd, char **envp)
{
	dup2(cmd_struct.infile_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(cmd_struct.infile_fd);
	close(pipe_fd[1]);
	execute_cmd(cmd_struct.cmd_path, envp);
}

void	second_child(t_pipex cmd_struct, int *pipe_fd, char **envp)
{
	dup2(cmd_struct.outfile_fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(cmd_struct.outfile_fd);
	close(pipe_fd[0]);
	execute_cmd(cmd_struct.cmd_path, envp);
}

int main (int ac, char **av, char **envp)
{
	t_pipex	first_cmd;
	t_pipex	second_cmd;
	int	pipe_fd[2];
	int pid1;
	int pid2;

	if (ac == 5)
	{
		first_cmd.cmd_path = get_path(av[2], envp);
		first_cmd.infile_fd = open(av[1], O_RDONLY);
		second_cmd.cmd_path = get_path(av[3], envp);
		second_cmd.outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipe(pipe_fd) == -1)
			return (1);
		pid1 = fork();
		if (pid1 == -1)
			return (2);
		else if (pid1 == 0)
			first_child(first_cmd, pipe_fd, envp);
		pid2 = fork();
		if (pid2 == 0)
			second_child(second_cmd, pipe_fd, envp);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (1);
}
