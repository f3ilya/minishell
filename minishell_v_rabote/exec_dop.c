#include "minishell.h"

void	child_status(t_param *p)
{
	if (WIFEXITED(p->pid))
		p->status = WEXITSTATUS(p->pid);
	if (WIFSIGNALED(p->pid))
		p->status = WTERMSIG(p->pid);
}

int	ft_execve(char **cmd, char *str, int pipe, t_param *p)
{
	if (!pipe)
		p->pid = fork();
	if (!pipe && p->pid < 0)
		return (err_out("execve: ", "failed to create a new process.", 1, -1, p));
	if (!p->pid)
		if (execve(str, cmd, p->env) == -1)
			return (err_out("command not found: ", cmd[0], 127, -1, p));
	if (pipe)
		return (1);
	wait(&p->pid);
	child_status(p);
	p->pid = 0;
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

int	err_out(char *str, char *str2, int status, int out, t_param *p)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	if (status >= 0)
		p->status = status;
	return (out);
}
