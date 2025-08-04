#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

char	*get_path(char *cmd, char **envp);
void	free_arr(char **arr);
void	execute_cmd(char *cmd, char **envp);
void	error_exit(void);
void	cmd_not_found(char *cmd);
void	close_pipe(int *pipe_fd);
int		file_open(char *file, int io_flag);

#endif
