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
//void	first_child(char *cmd, char **envp, int *pipe_fd, int infile)
//{
//	if (dup2(infile, STDIN_FILENO) == -1)
//		error_exit();
//	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
//		error_exit();
//	close(infile);
//	close_pipe(pipe_fd[0], pipe_fd[1]);
//	execute_cmd(cmd, envp);
//}
//
//void	second_child(char *cmd, char **envp, int *pipe_fd, int outfile)
//{
//	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
//		error_exit();
//	if (dup2(outfile, STDOUT_FILENO) == -1)
//		error_exit();
//	close(outfile);
//	close_pipe(pipe_fd[0], pipe_fd[1]);
//	execute_cmd(cmd, envp);
//}
//
//void	fork_process(char **av, char **envp, int infile, int outfile)
//{
//	int	pipe_fd[2];
//	int	pid_s[2];
//
//	if (pipe(pipe_fd) == -1)
//		error_exit();
//	pid_s[0] = fork();
//	if (pid_s[0] == -1)
//		error_exit();
//	else if (pid_s[0] == 0)
//	{
//		close(outfile);
//		first_child(av[2], envp, pipe_fd, infile);
//	}
//	pid_s[1] = fork();
//	if (pid_s[1] == -1)
//		error_exit();
//	else if (pid_s[1] == 0)
//	{
//		close(infile);
//		second_child(av[3], envp, pipe_fd, outfile);
//	}
//	close_pipe(infile, outfile);
//	close_pipe(pipe_fd[0], pipe_fd[1]);
//	waitpid(pid_s[0], NULL, 0);
//	waitpid(pid_s[1], NULL, 0);
//}
//
//void	open_files(char **av, char **envp)
//{
//	int	infile;
//	int	outfile;
//	
//	infile = open(av[1], O_RDONLY);
//	if (infile == -1)
//		error_exit();
//	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (outfile == -1)
//		error_exit();
//	fork_process(av, envp, infile, outfile);
//}
//
//int	main(int ac, char **av, char **envp)
//{
//
//	if (ac != 5)
//		return (ft_putstr_fd("Usage: ./pipex infile cmd cmd outfile\n", 2), 1);
//	open_files(av, envp);
//	return (1);
//}
