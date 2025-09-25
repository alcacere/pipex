#include "pipex.h"

void	set_heredoc_infile(t_fds *fds, char *here_delimiter)
{
	char *line;

	line = NULL;
	if (pipe(fds->buff_pipe) == -1)
		error_exit("pipe failed in set heredoc");
	while (1)
	{
		line = get_next_line(fds->infile);
		if (!line)
			break ;
		if (ft_strcmp(line, here_delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fds->buff_pipe[1]);
		free(line);
	}
	free(here_delimiter);
	dup2(fds->buff_pipe[0], STDIN_FILENO);
	close(fds->buff_pipe[0]);
	close(fds->buff_pipe[1]);
}

void	child_heredoc(char *cmd, char **envp, t_fds fds)
{
	close(fds.pipes[0]);
	if (fds.last_cmd == 1)
	{
		if (dup2(fds.outfile, STDOUT_FILENO) == -1)
		{
			close(fds.outfile);
			close(fds.pipes[1]);
			error_exit("dup2 failed in child");
		}
	}
	else
	{
		if (dup2(fds.pipes[1], STDOUT_FILENO) == -1)
		{
			close(fds.outfile);
			close(fds.pipes[1]);
			error_exit("dup2 failed in child");
		}
	}
	close(fds.outfile);
	close(fds.pipes[1]);
	execute_cmd(cmd, envp);
}

static void	create_pipeline_heredoc(char **envp, t_fds fds)
{
	int i;

	i = 0;
	while (i <= fds.num_cmds - 1)
	{
		if (pipe(fds.pipes) == -1)
			error_exit("pipe failed");
		if (i == fds.num_cmds - 1)
			fds.last_cmd = 1;
		fds.pid = fork();
		if (fds.pid == -1)
			error_exit("fork failed");
		if (fds.pid == 0)
			child_heredoc(fds.args[i], envp, fds);
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

void	do_pipe_here_doc(char *here_delimiter, char **envp, t_fds fds)
{
	set_heredoc_infile(&fds, here_delimiter);
	create_pipeline_heredoc(envp, fds);
	wait_children(fds.num_cmds);
}
