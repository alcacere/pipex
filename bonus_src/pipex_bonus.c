/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 03:15:02 by alcacere          #+#    #+#             */
/*   Updated: 2025/10/06 03:30:04 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

//static void	init_common_fds(t_fds *fds)
//{
//	fds->pipes[0] = 0;
//	fds->pipes[1] = 0;
//	fds->pid = -1;
//	fds->last_cmd = 0;
//}
//
static void	init_fds(t_fds *fds, int ac, char **av, int here_doc)
{
	if (here_doc)
	{
		fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		fds->infile = 0;
		fds->num_cmds = ac - 4;
		fds->args = av + 3;
		fds->pid = -1;
	}
	else
	{
		fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fds->infile = open(av[1], O_RDONLY);
		fds->num_cmds = ac - 3;
		fds->args = av + 2;
		fds->pid = -1;
	}
	if (fds->outfile == -1 || fds->infile == -1)
		error_exit("open failed");
}

static void	child_routine(char *cmd, char **envp, t_fds fds)
{
	int		out_fd;

	close(fds.pipes[0]);
	if (fds.last_cmd)
		out_fd = fds.outfile;
	else
		out_fd = fds.pipes[1];
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		error_exit("dup2 failed");
	close(fds.outfile);
	close(fds.pipes[1]);
	execute_cmd(cmd, envp);
}

static void	parent_routine(t_fds *fds)
{
	close(fds->pipes[1]);
	if (dup2(fds->pipes[0], STDIN_FILENO) == -1)
		error_exit("dup2 failed in parent routine");
	close(fds->pipes[0]);
}

static pid_t	create_pipeline(char **envp, t_fds *fds, int is_heredoc)
{
	int	i;

	i = 0;
	if (!is_heredoc)
	{
		dup2(fds->infile, STDIN_FILENO);
		close(fds->infile);
	}
	while (i < fds->num_cmds)
	{
		if (i == fds->num_cmds - 1)
			fds->last_cmd = 1;
		if (pipe(fds->pipes) == -1)
			error_exit("pipe failed");
		fds->pid = fork();
		if (fds->pid == -1)
			error_exit("fork failed");
		else if (fds->pid == 0)
			child_routine(fds->args[i], envp, *fds);
		else
			parent_routine(&fds);
		i++;
	}
	return (fds->pid);
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;
	char	*here_delimiter;
	pid_t	last_pid;

	if (ac < 5)
		error_exit("too few arguments");
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		here_delimiter = ft_strjoin(av[2], "\n");
		init_fds(&fds, ac, av, 1);
		set_heredoc_infile(&fds, here_delimiter);
		last_pid = create_pipeline(envp, &fds, 1);
	}
	else
	{
		init_fds(&fds, ac, av, 0);
		last_pid = create_pipeline(envp, &fds, 0);
	}
	close(fds.outfile);
	return (get_exit_status(last_pid));
}
