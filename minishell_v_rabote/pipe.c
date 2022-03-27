#include "minishell.h"

void	child(t_arg *arg, int fd, int end[2])
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (arg->next)
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
	}
}

int run_pipe(t_arg *arg, t_param *p, int fd)
{
	int end[2];

	if (pipe(end))
		return (-1);
	p->pid = fork();
	if (p->pid < 0)
	{
		close(end[0]);
		close(end[1]);
		close(fd);
		return (-1);
	}
	else if (!p->pid)
	{
		child(arg, fd, end);
		exec(arg->arg, 1, p);
	}
	wait(&p->pid);
	child_status(p);
	close(end[1]);
	close(fd);
	return (end[0]);
}

void	pipe_list(t_arg *arg, t_param *p)
{
	int fd = 0;
	while (arg)
	{
		fd = run_pipe(arg, p, fd);
		arg = arg->next;
	}
	close(fd);
}