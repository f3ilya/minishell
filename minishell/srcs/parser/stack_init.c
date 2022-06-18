/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:02:56 by                   #+#    #+#             */
/*   Updated: 2021/12/07 13:02:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	gaps_redir(char *s, int *i)
{
	if (s[*i] == '\'')
	{
		while (s[++*i] != '\'' && s[*i] != '\0')
			;
	}
	if (s[*i] == '\"')
	{
		while (s[++*i] != '\"' && s[*i] != '\0')
			if (s[*i] == '\\' && s[*i + 1] == '\"')
				(*i)++;
	}
}

char	*stack_add_elem(char *s, int *i, t_list2 **stack)
{
	char	*new_s;
	int		pipe;

	pipe = 0;
	if (s[*i] == '|')
		pipe = 1;
	ft_lstadd_back2(stack, ft_lstnew2(ft_substr(s, 0, *i), pipe));
	while ((s[*i + 1] == ' ' || s[*i + 1] == '\t' || s[*i + 1] == '|'))
		(*i)++;
	new_s = ft_strdup(s + *i + 1);
	free(s);
	*i = -1;
	return (new_s);
}

int	stack_init(char *s, t_list2 **stack)
{
	int	i;

	if (pre_parser(s) != 0)
		return (1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' || s[i] == ';')
		{
			s = stack_add_elem(s, &i, stack);
			continue ;
		}
		if (s[i] == '\'' || s[i] == '\"')
			gaps_redir(s, &i);
		if (s[i] == '\\' && s[i + 1] != '\0')
			i += 1;
	}
	if (*s != '\0')
		ft_lstadd_back2(stack, ft_lstnew2(s, 0));
	return (0);
}

int	stack_clean(t_list2 *lst)
{
	t_list2	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->pre_com);
		free(lst);
		lst = next;
	}
	return (0);
}
