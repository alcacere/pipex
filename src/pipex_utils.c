#include "pipex.h"

int	file_open(char *file, int io_flag)
{
	int	fd;

	if (!file)
		return (-1);
	if (io_flag == 0)
	{
		fd = open(file, O_RDONLY);
		return (fd);
	}
	else if (io_flag == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	return (-1);
}

char	*find_path(char **full_path, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while (full_path[i])
	{
		tmp = ft_strjoin(full_path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**full_path;
	char	*cmd_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':');
	cmd_path = find_path(full_path, cmd);
	free_arr(full_path);
	return (cmd_path);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		free_arr(cmd_args);
		error_exit();
	}
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_arr(cmd_args);
		cmd_not_found(cmd);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_arr(cmd_args);
		free(cmd_path);
		error_exit();
	}
}
