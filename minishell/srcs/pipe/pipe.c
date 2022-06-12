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

void	child(t_list2 *arg, int fd, int end[2])
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (arg->next)
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
	}
//	else
//		dup2(fd, STDOUT_FILENO);
}

int	run_pipe(t_list2 *arg, t_param *p, int fd)
{
	int	end[2];

	if (pipe(end))
		return (-1);
	signal(SIGINT, SIG_IGN);
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
		p->pipe = 1;
		exec(ft_split(arg->pre_com, ' '), p);
		ft_exit(0);
	}
//	wait(&p->pid);
//	child_status(p);
	close(end[1]);
	close(fd);
	return (end[0]);
}

void	pipe_list(t_list2 *arg, t_param *p)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	while (arg)
	{
		fd_on(arg, 0);
		fd = run_pipe(arg, p, fd);
		fd_on(arg, 1);
		arg = arg->next;
	}
//	close(fd);
//	dup2(fd, STDIN_FILENO);
//	wait(&p->pid);
	while (waitpid(-1, &p->pid, 0) > 0)
		;
	child_status(p);
	signal(SIGINT, signal_int);
//	dup2(fd, STDOUT_FILENO);
	p->pipe = 0;
	p->pid = 0;
	close(fd);
}
