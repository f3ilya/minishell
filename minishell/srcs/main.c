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
#include "../includes/minishell.h"

static void	execute2(t_list2 *stack, t_param *p, int pipe)
{
	stack->fdd0 = dup(STDIN_FILENO);
	stack->fdd1 = dup(STDOUT_FILENO);
	fd_on(stack, 0);
	if (pipe)
		pipe_list(stack, p);
	else
		exec(ft_split(stack->pre_com, ' '), p);
	fd_on(stack, 1);
}

void    signal_int(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	param_init(char **env, t_param *p)
{
	int n;

	n = 0;
	while (env[n])
		n++;
	p->env = malloc(sizeof (char *) * (n + 1));
	n = -1;
	while (env[++n])
		p->env[n] = ft_strdup(env[n]);
	p->env[n] = NULL;
	p->pid = 0;
}

int	execute(char *input, char **env, t_param *p)
{
	int		n;
	int		pipe;
	t_list2 *stack;
	t_list2	*lst;

	stack = NULL;
	n = stack_init(input, &stack);
	if (n)
		return (1);
	lst = stack;
	while (lst)
	{
		parser(lst, env);
		if (errno != 0)
			return (errno);
		if (lst->pipe)
			pipe = 1;
		lst = lst->next;
	}
	execute2(stack, p, pipe);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	*shell_prompt;
	int		i;
	t_param	p;

	param_init(env, &p);
	signal(SIGINT, signal_int);
	signal(SIGQUIT, SIG_IGN);
	g_status = 0;
	i = -1;
	while(++i >= 0)
	{
		shell_prompt = "minishell> ";
		input = readline(shell_prompt);
		if (!input)
			break;
		if (input[0] == '\0')
			continue;
//		printf("1\n");
		add_history(input);
		//printf("%s", input);
		execute(input, env, &p);
//		free(input);
//		printf("3\n");
	}
	return (0);
}
