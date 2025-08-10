#include "pipex.h"

void	child_process(char *cmd, char **envp, int *fds, int io_flags)
{
	if (io_flags == fds[0])
	{
		dup2(fds[2], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[3], STDOUT_FILENO);
	}
	close_all_fds(fds);
	execute_cmd(cmd, envp);
}

static void	run_pipex(char **av, char **envp)
{
	int	fds[4];
	int	pids[2];

	fds[2] = open(av[1], O_RDONLY);
	if (fds[2] == -1)
		error_exit("Infile open failed");
	fds[3] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[3] == -1)
		error_exit("Outfile open failed");
	if (pipe(fds) == -1)
		error_exit("Pipe creation failed");
	pids[0] = fork();
	if (pids[0] == -1)
		error_exit("Fork failed");
	if (pids[0] == 0)
		child_process(av[2], envp, fds, fds[0]);
	pids[1] = fork();
	if (pids[1] == -1)
		error_exit("Fork failed");
	if (pids[1] == 0)
		child_process(av[3], envp, fds, fds[1]);
	close_all_fds(fds);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

int main (int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	run_pipex(av, envp);
	return (0);
}
