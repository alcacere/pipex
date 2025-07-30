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

int	file_open(char *file, int io_flag)
{
	int	fd;

	if (io_flag == 0)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
				error_exit("Cannot open fd");
		return (fd);
	}
	else if (io_flag == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			error_exit("Cannot open fd");
		return (fd);
	}
	error_exit("Invalid fd");
	return (-1);
}

char *get_path(char *cmd, char **envp)
{
	char **full_path;
	char *cmd_path;
	char *tmp;
	int i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		tmp = ft_strjoin(full_path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_arr(full_path), cmd_path);
		free(cmd_path);
		i++;
	}
	free_arr(full_path);
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp)
{
	char **cmd_args;
	char *cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		error_exit("command parsing failed");
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_arr(cmd_args);
		cmd_not_found(cmd);
	}
	execve(cmd_path, cmd_args, envp);
	free_arr(cmd_args);
	free(cmd_path);
}

//int main (int ac, char **av, char **envp)
//{
//	if (ac == 2)
//	{
//		execute_cmd(av[1], envp);
//	}
//}
