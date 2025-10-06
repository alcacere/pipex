/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clean_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 03:35:21 by alcacere          #+#    #+#             */
/*   Updated: 2025/10/06 03:35:24 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	cmd_not_found(char *cmd)
{
	char	**command;

	command = ft_split(cmd, ' ');
	if (!command)
		exit(1);
	ft_putstr_fd(command[0], 2);
	free_arr(command);
	ft_putstr_fd(": Command not found\n", 2);
	exit(127);
}

int	get_exit_status(pid_t last_pid)
{
	int	status;
	int	exit_code;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 1;
	while (wait(NULL) != -1)
		;
	return (exit_code);
}
