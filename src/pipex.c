#include "pipex.h"

void init_fds(t_fds *fds, int ac, char **av, int here_doc)
{
	if (here_doc)
	{
		fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->outfile == -1)
			error_exit("open failed in init");
		fds->infile = 0;
		fds->num_cmds = ac - 4;
		fds->args = av + 3;
	}
	else
	{
		fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fds->infile = open(av[1], O_RDONLY);
		if (fds->outfile == -1 || fds->infile == -1)
			error_exit("open failed in init");
		fds->num_cmds = ac - 3;
		fds->args = av + 2;
	}
	fds->pipes[0] = 0;
	fds->pipes[1] = 0;
	fds->pid = -1;
	fds->last_cmd = 0;
}

void	child_process(char *cmd, char **envp, t_fds fds)
{
	close(fds.pipes[0]);
	if (fds.last_cmd == 1)
	{
		if (dup2(fds.outfile, STDOUT_FILENO) == -1)
		{
			close(fds.infile);
			close(fds.outfile);
			close(fds.pipes[1]);
			error_exit("dup2 failed in child");
		}
	}
	else
	{
		if (dup2(fds.pipes[1], STDOUT_FILENO) == -1)
		{
			close(fds.infile);
			close(fds.outfile);
			close(fds.pipes[1]);
			error_exit("dup2 failed in child");
		}
	}
	close(fds.infile);
	close(fds.outfile);
	close(fds.pipes[1]);
	execute_cmd(cmd, envp);
}

static void	create_pipeline(char **envp, t_fds fds)
{
	int i;

	i = 0;
	dup2(fds.infile, STDIN_FILENO);
	close(fds.infile);
	while (i <= fds.num_cmds - 1)
	{
		if (i == fds.num_cmds - 1)
			fds.last_cmd = 1;
		if (pipe(fds.pipes) == -1)
			error_exit("pipe failed");
		fds.pid = fork();
		if (fds.pid == -1)
			error_exit("fork failed");
		if (fds.pid == 0)
			child_process(fds.args[i], envp, fds);
		else
		{
			close(fds.pipes[1]);
			dup2(fds.pipes[0], STDIN_FILENO);
			close(fds.pipes[0]);
		}
		i++;
	}
	close(fds.outfile);
}


void	do_pipe(char **envp, t_fds fds)
{
	create_pipeline(envp, fds);
	wait_children(fds.num_cmds);
}

int main (int ac, char **av, char **envp)
{
	t_fds fds;
	char *here_delimiter;

	if (ac < 5)
		error_exit("too few arguments");
	if (ft_strcmp(av[1], "heredoc") == 0)
	{
		here_delimiter = ft_strjoin(av[2], "\n");
		init_fds(&fds, ac, av, 1);
		do_pipe_here_doc(here_delimiter ,envp, fds);
		return (EXIT_SUCCESS);
	}
	else
	{
		init_fds(&fds, ac, av, 0);
		do_pipe(envp, fds);
		return (EXIT_SUCCESS);
	}
}
