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

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_space(char *s, int *i)
{
	if (s[*i] == '>')
		++(*i);
	while (is_space(s[++(*i)]))
		;
}

int	create_file(char *file_name, const char *s, t_list2 *elem)
{
	if (*s == '<')
		elem->fd0 = open(file_name, O_RDONLY);
	else if (*(s + 1) == '>')
		elem->fd1 = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (*s == '>')
		elem->fd1 = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		printf("shit happened in redirect computing\n");
	if (errno != 0)
		printf("minishell: %s: %s\n", strerror(errno), file_name);
	return (errno);
}

char	*end_of_filename(char *s, int *i, char **env)
{
	while (s[++(*i)] && !is_space(s[*i]))
	{
		if (s[*i] == '\'')
			s = gap(s, i);
		if (s[*i] == '\"')
			s = gap2(s, i, env);
		if (s[*i] == '\\')
			s = slash(s, i);
		if (s[*i] == '$')
			s = dollar(s, i, env);
	}
	return (s);
}

char	*redirects(char *s, int *i, t_list2 *elem, char **env)
{
	int		first_letter;
	int		start_pos;
	char	*file_name;
	char	*beginning;
	char	*ending;

	start_pos = *i - 1;
	skip_space(s, i);
	first_letter = *i;
	s = end_of_filename(s, i, env);
	file_name = ft_substr(s, first_letter, *i - first_letter);
	create_file(file_name, &s[start_pos + 1], elem);
	beginning = ft_substr(s, 0, start_pos + 1);
	ending = ft_strdup(s + *i);
	free(s);
	s = ft_strjoin(beginning, ending);
	free(beginning);
	free(ending);
	free(file_name);
	*i = start_pos;
	return (s);
}
