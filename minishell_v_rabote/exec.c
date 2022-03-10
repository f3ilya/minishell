#include "minishell.h"

int	check_stat(char **cmd, char *str, struct stat stat, int pipe)
{
	if (stat.st_mode & S_IFREG)
	{
		if (stat.st_mode & S_IXUSR)
			return (ft_execve(cmd, str, pipe));
		else
			return (err_out("permission denied: ", str, 1, 1));
	}
	else
		return (err_out("is a directory: ", cmd[0], 1, 1));
}

int	check_bin(char **cmd, int pipe)
{
	struct stat	stat;
	char		**path;
	char		*str;
	char		*tmp;
	int			i;

	i = -1;
	path = my_path();
	if (!path)
		return (-1);
	while (path[++i])
	{
		if (cmd[0][0] == '/')
			str = cmd[0];
		else
		{
			tmp = ft_strjoin(path[i], "/");
			str = ft_strjoin(tmp, cmd[0]);
		}
		if (!lstat(str, &stat))
			return (check_stat(cmd, str, stat, pipe));
		free(str);
	}
	return (0);
}

int	check_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (11);
		//return (my_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (12);
		//return (my_cd(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		return (13);
		//return (my_pwd(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (14);
		//return (my_export(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (15);
		//return (my_unset(cmd));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (16);
		//return (my_env(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (17);
		//my_exit(cmd);
	return (0);
}

int	exec(char **cmd, int pipe)
{
	int ret1;
	int	ret2;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (-1);
	ret1 = check_builtin(cmd);
	if (ret1)
		return (ret1);
	if (ret1 < 0)
		return (-1);
	ret2 = check_bin(cmd, pipe);
	if (ret2)
		return (ret2);
	/*if (check_builtin(cmd) || check_bin(cmd, pipe))
		return (1);*/
	return (10);
}
