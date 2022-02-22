#include "minishell.h"

int	ft_execve(char **cmd, char *str, int pipe)
{
	pid_t 	pid;

	pid = fork();
	if (pid < 0)
		return (err_out("execve: ", "bad fork", 1, -1));
	if (pid == 0)
		if (execve(str, cmd, g_env) == -1)
			return (err_out("command not found: ", cmd[0], 127, -1));
	waitpid(pid, NULL, 0);
	return (1);
}

char	**my_path()
{
	char	*env;
	char	**path;

	env = getenv("PATH");
	if (!env)
		return (NULL);
	path = ft_split(ft_substr(env, 5, ft_strlen(env)), ':');
	return (path);
}

int	err_out(char *str, char *str2, int status, int out)
{
	ft_putendl_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
	ft_putendl_fd(str2, 2);
	ft_putendl_fd("\n", 2);
	if (status != 0)
		g_status = status;
	return (out);
}
