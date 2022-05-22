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

void    signal_int(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	*shell_prompt;

	signal(SIGINT, signal_int);
	signal(SIGQUIT, SIG_IGN);

	int i = -1;
	while(++i >= 0)
	{
		shell_prompt = "minishell> ";
		input = readline(shell_prompt);
		if (!input)
			break;
		add_history(input);
		execute(input, env);
		free(input);
	}
	return (0);
}
