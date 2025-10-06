/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:46:04 by alcacere          #+#    #+#             */
/*   Updated: 2025/08/14 02:46:08 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

char	*get_cmd_path(char *cmd, char **envp);
char	**get_env_path(char **envp);
char	*find_path(char *cmd, char **envp);
void	execute_cmd(char *cmd, char **envp);
void	free_arr(char **arr);
void	error_exit(char *msg);
void	cmd_not_found(char *cmd);
void	close_all_fds(int *fds);

#endif
