#ifndef PIPEX_H
#define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_pipex{
	int infile_fd;
	int outfile_fd;
	char *cmd_path;
}	t_pipex;

char	*get_path(char *cmd, char **envp);
void	free_arr(char **arr);
void	execute_cmd(char *cmd, char **envp);
void	error_exit(char *msg);
void	cmd_not_found(char *cmd);

#endif // !"PIPEX_H"

