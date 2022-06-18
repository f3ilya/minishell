/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:24:06 by                   #+#    #+#             */
/*   Updated: 2022/01/30 20:21:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	check(char **args, t_param *p)
{
	struct stat	f;
	int			flag;

	if (lstat(args[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR && (args[0][ft_strlen(args[0]) - 1] == '/'
			|| !ft_strncmp(args[0], "./", 2)))
			return (err_out(args[0], ": Is a directory", 126, 0));
		else if ((!ft_strncmp(args[0], "./", 2) || !ft_strncmp(args[0], "/", 1))
			&& (f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
			return (ft_execve(args, ft_strdup(args[0]), p));
		else if (flag != S_IXUSR && flag != S_IRUSR
			&& flag != S_IFDIR && flag != S_IFLNK)
			return (err_out(args[0], ": Permission denied", 126, 0));
	}
	else if (!ft_strncmp(args[0], "./", 2) || args[0][0] == '/')
	{
		return (err_out(args[0], ": No such file or directory", 127, 0));
	}
	return (err_out(args[0], ": command not found", 127, 0));
}

int	check_stat(char **cmd, char *str, struct stat stat, t_param *p)
{
	if (stat.st_mode & S_IFREG)
	{
		if (stat.st_mode & S_IXUSR)
			return (ft_execve(cmd, str, p));
		else
		{
			ft_putstr_fd("minishell: execve: permission denied: ", 2);
			ft_putendl_fd(str, 2);
			g_status = 1;
			free(str);
			return (1);
		}
	}
	else
		return (err_out(cmd[0], ": Is a directory", 1, 1));
}

int	check_bin(char **cmd, t_param *p, char **path)
{
	struct stat	stat;
	char		*str;
	char		*tmp;
	int			i;

	i = -1;
	if (!path && cmd[0][0] == '/')
	{
		str = cmd[0];
		if (!lstat(str, &stat))
			return (check_stat(cmd, str, stat, p));
	}
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!lstat(str, &stat))
			return (check_stat(cmd, str, stat, p));
		free(str);
	}
	return (0);
}

int	check_builtin(char **cmd, t_param *p)
{
	char	*pwd;

	if (!ft_strncmp(cmd[0], "echo", 5))
		return (my_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (my_cd(cmd, p));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
	{
		pwd = getcwd(NULL, 0);
		ft_putendl_fd(pwd, 1);
		free(pwd);
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (my_export(cmd, p));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (my_unset(cmd, p));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (my_env(p));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		my_exit(cmd);
	return (0);
}

int	exec(char **cmd, t_param *p)
{
	int		ret1;
	int		ret2;
	char	**path;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (-1);
	ret1 = check_builtin(cmd, p);
	if (ret1)
		return (ret1);
	if (ret1 < 0)
		return (-1);
	path = my_path(p);
	ret2 = check_bin(cmd, p, path);
	ft_free(path);
	if (ret2)
		return (ret2);
	if (ret2 < 0)
		return (-1);
	check(cmd, p);
	return (0);
}
