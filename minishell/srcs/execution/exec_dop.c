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

void	child_status(t_param *p)
{
	if (WIFEXITED(p->pid))
		g_status = WEXITSTATUS(p->pid);
	if (WIFSIGNALED(p->pid))
	{
		g_status = WTERMSIG(p->pid);
		if (g_status != 131)
			g_status += 128;
	}
}

int	ft_execve(char **cmd, char *str, t_param *p)
{
	if (!p->pipe)
	{
		signal(SIGINT, SIG_IGN);
		p->pid = fork();
	}
	if (!p->pipe && p->pid < 0)
		return (err_out("execve: ", "failed to create a new process.", 1, -1));
	if (!p->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(str, cmd, p->env) == -1)
		{
			err_out("command not found: ", cmd[0], 127, -1);
			ft_exit(0);
		}
	}
	free(str);
	if (p->pipe)
		return (1);
	wait(&p->pid);
	signal(SIGINT, signal_int);
	child_status(p);
	p->pid = 0;
	return (1);
}

char	**my_path(t_param *p)
{
	char	*env;
	char	**path;
	char	*path_long;

	env = get_env("PATH", p);
	if (!env)
		return (NULL);
	path_long = ft_substr(env, 0, ft_strlen(env));
	path = ft_split(path_long, ':');
	free(env);
	free(path_long);
	return (path);
}

int	err_out(char *str, char *str2, int status, int out)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	if (status >= 0)
		g_status = status;
	return (out);
}

void	fd_on(t_list2 *stack, int off)
{
	if (off)
	{
		dup2(stack->fdd0, STDIN_FILENO);
		dup2(stack->fdd1, STDOUT_FILENO);
	}
	else
	{
		dup2(stack->fd0, STDIN_FILENO);
		dup2(stack->fd1, STDOUT_FILENO);
	}
}
