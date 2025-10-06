/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 03:14:42 by alcacere          #+#    #+#             */
/*   Updated: 2025/10/06 03:36:23 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	set_heredoc_infile(t_fds *fds, char *here_delimiter)
{
	char	*line;

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
