#include "minishell.h"

static char *add_home(char *cmd)
{
	char *home;
	char *tmp;

	if (!ft_strncmp(cmd, "~/", 2))
	{
		home = getenv("HOME");
		if (home)
		{
			tmp = ft_strjoin(home, ft_substr(cmd, 1, ft_strlen(cmd)));
			return (tmp);
		}
	}
	return (cmd);
}

static int change(char *cmd, t_param *p)
{
	char *pwd;

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
	struct stat f;

	if (!change(cmd, p))
	{
		if (stat(cmd, &f) == -1)
			return (err_out("cd: ", "No such file or directory", 127, 1, p));
		else if (!(f.st_mode & S_IXUSR))
			return (err_out("cd: ", "Permission denied", 1, 1, p));
		else
			return (err_out("cd: ", "Not a directory", 1, 1, p));
	}
	return (1);
}

static int check_path(char *cmd, t_param *p)
{
	char *tmp;

	if (!ft_strncmp(cmd, "-", 2))
	{
		tmp = getenv("OLDPWD");
		if (!tmp)
			return (err_out("cd: ", "OLDPWD not set", 1, 1, p));
		check_directory(tmp, p);
		free(tmp);
		tmp = getenv("PWD");
		if (!tmp)
			return (err_out("cd: ", "PWD not set", 1, 1, p));
		ft_putendl_fd(tmp, 1);
		free(tmp);
		return (1);
	}
	return (check_directory(cmd, p));
}

int my_cd(char **cmd, t_param *p)
{
	char *home;

	home = NULL;
	if (cmd && cmd[1] && cmd[2])
		return (err_out(cmd[0], ": too many arguments", 0, 1, p));
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", 2) || !ft_strncmp(cmd[1], "--", 3))
	{
		home = getenv("HOME");
		if (!home)
			return (err_out(cmd[0], ": HOME not set", 0, 1, p));
		return (check_directory(home, p));
	}
	return (check_path(add_home(cmd[1]), p));
}
