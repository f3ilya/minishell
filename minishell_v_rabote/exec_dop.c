#include "minishell.h"

void	child_status(void)
{
	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
		g_status = WTERMSIG(g_pid);
}

int	ft_execve(char **cmd, char *str, int pipe)
{
	if (!pipe)
		g_pid = fork();
	if (!pipe && g_pid < 0)
		return (err_out("execve: ", "failed to create a new process.", 1, -1));
	if (!g_pid)
		if (execve(str, cmd, g_env) == -1)
			return (err_out("command not found: ", cmd[0], 127, -1));
	if (pipe)
		return (1);
	wait(&g_pid);
	child_status();
	g_pid = 0;
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
