#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_fds {
	int infile;
	int outfile;
	int pipes[2];
	int buff_pipe[2];
	int pid;
	int last_cmd;
	int num_cmds; 
	char **args;
} t_fds;

char	*get_cmd_path(char *cmd, char **envp);
char	**get_env_path(char **envp);
char	*find_path(char *cmd, char **envp);
void	execute_cmd(char *cmd, char **envp);
void	free_arr(char **arr);
void	wait_children(int num_cmds);
void	error_exit(char *msg);
void	cmd_not_found(char *cmd);
void	set_heredoc_infile(t_fds *fds, char *here_delimiter);
int		get_exit_status(pid_t last_pid);

#endif
