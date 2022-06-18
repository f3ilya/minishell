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

static char	*add_home(char *cmd, t_param *p)
{
	char	*home;
	char	*tmp;
	char	*sub;

	if (!ft_strncmp(cmd, "~/", 2))
	{
		home = get_env("HOME", p);
		if (home)
		{
			sub = ft_substr(cmd, 1, ft_strlen(cmd));
			tmp = ft_strjoin_free_source(home, sub);
			return (tmp);
		}
	}
	return (cmd);
}

static int	change(char *cmd, t_param *p)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(cmd))
	{
		set_env("OLDPWD=", pwd, p);
		free(pwd);
		pwd = getcwd(NULL, 0);
		set_env("PWD=", pwd, p);
		free(pwd);
		return (1);
	}
	return (0);
}

static int	check_directory(char *cmd, t_param *p)
{
	struct stat	f;

	if (!change(cmd, p))
	{
		if (stat(cmd, &f) == -1)
			return (err_out("cd: ", "No such file or directory", 127, 1));
		else if (!(f.st_mode & S_IXUSR))
			return (err_out("cd: ", "Permission denied", 1, 1));
		else
			return (err_out("cd: ", "Not a directory", 1, 1));
	}
	return (1);
}

static int	check_path(char *cmd, t_param *p)
{
	char	*tmp;

	if (!ft_strncmp(cmd, "-", 2))
	{
		tmp = get_env("OLDPWD", p);
		if (!tmp)
			return (err_out("cd: ", "OLDPWD not set", 1, 1));
		check_directory(tmp, p);
		free(tmp);
		tmp = get_env("PWD", p);
		if (!tmp)
			return (err_out("cd: ", "PWD not set", 1, 1));
		ft_putendl_fd(tmp, 1);
		free(tmp);
		return (1);
	}
	return (check_directory(cmd, p));
}

int	my_cd(char **cmd, t_param *p)
{
	char	*home;
	int		ret;
	char	*str;

	home = NULL;
	if (cmd && cmd[1] && cmd[2])
		return (err_out(cmd[0], ": too many arguments", 0, 1));
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", 2) || !ft_strncmp(cmd[1], "--", 3))
	{
		home = get_env("HOME", p);
		if (!home)
			return (err_out(cmd[0], ": HOME not set", 0, 1));
		ret = check_directory(home, p);
		free(home);
		return (ret);
	}
	str = add_home(cmd[1], p);
	ret = check_path(str, p);
	if (!ft_strncmp(cmd[1], "~/", 2))
		free(str);
	return (ret);
}
