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

char	*form_result_string(int *i, int j, char *s, char *value)
{
	char	*beginning;
	char	*ending;
	char	*res1;

	beginning = ft_substr(s, 0, j);
	ending = ft_strdup(s + *i);
	res1 = ft_strjoin(beginning, value);
	*i = j - 1;
	free(s);
	if (res1)
	{
		s = ft_strjoin_free_source(res1, ending);
		*i = *i + ft_strlen(value);
	}
	else
		s = ft_strjoin_free_source(beginning, ending);
	return (s);
}
