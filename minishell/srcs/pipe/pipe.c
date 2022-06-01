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
		exec(arg->com, 1, p);
		ft_exit();
	}
	close(end[1]);
	close(fd);
	return (end[0]);
}

void	pipe_list(t_list2 *arg, t_param *p)
{
	int	fd;

	fd = dup(0);
	while (arg)
	{
		fd = run_pipe(arg, p, fd);
		arg = arg->next;
	}
	dup2(fd, STDOUT_FILENO);
	wait(&p->pid);
	child_status(p);
	signal(SIGINT, signal_int);
	close(fd);
}
