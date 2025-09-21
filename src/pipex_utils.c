#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	int	i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while(envp[i])
	{
		tmp = ft_strjoin(envp[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_env_path(char **envp)
{
	int	i;

	i = 0;
	while(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**env_path;
	char	*cmd_path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	cmd_path = find_path(cmd, env_path);
	free_arr(env_path);
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
		error_exit("Command parsing failed");
	}
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_arr(cmd_args);
		cmd_not_found(cmd);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free(cmd_path);
		free_arr(cmd_args);
		error_exit("execve failed");
	}
}

void	wait_children(int num_cmds)
{
	int i;

	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
}
