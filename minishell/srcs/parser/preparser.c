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

int	print_error(char *s, char tok)
{
	if (tok == 0)
		printf("minishell: %s\n", s);
	else
		printf("minishell: %s \'%c\'\n", s, tok);
	return (1);
}

int	gaps_local(char *s, int *i)
{
	if (s[*i] == '\'')
	{
		while (s[++*i] != '\'' && s[*i] != '\0')
			;
		if (s[*i] == '\0')
			return (print_error("synthax error: not paired quotes", 0));
	}
	if (s[*i] == '\"')
	{
		while (s[++*i] != '\"' && s[*i] != '\0')
			if (s[*i] == '\\' && s[*i + 1] == '\"')
				(*i)++;
		if (s[*i] == '\0')
			return (print_error("synthax error: not paired quotes", 0));
	}
	return (0);
}

int	pre_parser(char *s)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	if (s[i + 1] == ';' || s[i + 1] == '|')
		error += print_error("synthax error near unexpected token", s[i + 1]);
	while (s[++i] && error == 0)
	{
		if (s[i] == '|' && s[i + 1] == ';')
			error += print_error("synthax error near unexpected token", s[i]);
		if (s[i] == ';' && (s[i + 1] == '|' || s[i + 1] == ';'))
			error += print_error("synthax error near unexpected token", s[i]);
		if (s[i] == '\'' || s[i] == '\"')
			error += gaps_local(s, &i);
		if (s[i] == '\\' && s[i + 1] != '\0')
			i += 1;
	}
	if (error)
		return (error);
	if (s[i - 1] == '\\' || s[i - 1] == '|')
		error += print_error("synthax error near unexpected token", s[i - 1]);
	return (error);
}
