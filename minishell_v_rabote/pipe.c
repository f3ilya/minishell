#include "minishell.h"

void	child(t_arg *arg)
{
	close(arg->fd[0]);
	dup2(arg->fd[1], STDOUT_FILENO);
	close(arg->fd[1]);
	if (arg->next)
	{
		close(arg->fd[1]);
		dup2(arg->fd[0], STDIN_FILENO);
		close(arg->fd[0]);
	}
}

int run_pipe(t_arg *arg)
{
	if (pipe(arg->fd))
		return (-1);
	g_pid = fork();
	if (g_pid < 0)
	{
		close(arg->fd[0]);
		close(arg->fd[1]);
		return (-1);
	}
	else if (!g_pid)
	{
		child(arg);
		exec(arg->arg, 1);
	}
	wait(&g_pid);
	child_status();
	close(arg->fd[1]);
	return (arg->fd[0]);
}

void	pipe_list(t_arg *arg)
{
	while (arg)
	{
		run_pipe(arg);
		arg = arg->next;
	}
	close(arg->fd[0]);
}
