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

void	parser(t_list2 *elem, char **env)
{
	int		i;
	char	*s;

	s = elem->pre_com;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
			s = gap(s, &i);
		if (s[i] == '\"')
			s = gap2(s, &i, env);
		if (s[i] == '\\')
			s = slash(s, &i);
		if (s[i] == '$')
			s = dollar(s, &i, env);
		if (s[i] == '>' || s[i] == '<')
			s = redirects(s, &i, elem, env);
		if (errno != 0)
			return ;
	}
	elem->pre_com = s;
}

char	*dollar(char *s, int *i, char **env)
{
	int		j;
	int		k;
	int		len;
	char	*key;
	char	*value;

	j = *i;
	while (ft_isalnum(s[++(*i)]))
		;
	if (j == *i - 1)
		return (s);
	key = ft_substr(s, j + 1, *i - j - 1);
	len = ft_strlen(key);
	k = -1;
	while (env[++k])
		if (!ft_strncmp(env[k], key, len) && env[k][len] == '=')
			break ;
	free(key);
	value = NULL;
	if (env[k])
		value = ft_substr(env[k], len + 1, ft_strlen(env[k]) - len);
	s = form_result_string(i, j, s, value);
	return (s);
}

char	*slash(char *s, int *i)
{
	char	*beginning;
	char	*ending;
	char	*result;

	beginning = ft_substr(s, 0, *i);
	ending = ft_strdup(s + *i + 1);
	result = ft_strjoin_free_source(beginning, ending);
	free(s);
	return (result);
}

char	*gap(char *s, int *i)
{
	int		j;
	char	*beginning;
	char	*middle;
	char	*ending;
	char	*beg_plus_mid;

	j = *i;
	while (s[++(*i)] != '\'')
		;
	beginning = ft_substr(s, 0, j);
	middle = ft_substr(s, j + 1, *i - j - 1);
	ending = ft_strdup(s + *i + 1);
	free(s);
	beg_plus_mid = ft_strjoin_free_source(beginning, middle);
	s = ft_strjoin_free_source(beg_plus_mid, ending);
	*i = *i - 1;
	return (s);
}

char	*gap2(char *s, int *i, char **env)
{
	int		j;
	char	*beginning;
	char	*middle;
	char	*ending;
	char	*beg_plus_mid;

	j = *i;
	while (s[++(*i)] != '\"')
	{
		if (s[*i] == '\\' && (s[*i + 1] == '$' || s[*i + 1] == '\\'
				|| s[*i + 1] == '\"'))
				s = slash(s, i);
		if (s[*i] == '$')
			s = dollar(s, i, env);
	}
	beginning = ft_substr(s, 0, j);
	middle = ft_substr(s, j + 1, *i - j - 1);
	ending = ft_strdup(s + *i + 1);
	free(s);
	beg_plus_mid = ft_strjoin_free_source(beginning, middle);
	s = ft_strjoin_free_source(beg_plus_mid, ending);
	*i = *i - 1;
	return (s);
}
