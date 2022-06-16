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

void	set_env(char *env, char *new_env, t_param *p)
{
	int	i;

	i = -1;
	while (p->env[++i])
	{
		if (!ft_strncmp(p->env[i], env, ft_strlen(env)))
		{
			free(p->env[i]);
			p->env[i] = ft_strjoin(env, new_env);
			return ;
		}
	}
	p->env = realloc_env(i + 1, p);
	p->env[i] = ft_strjoin(env, new_env);
}

int	find_env(char *cmd, t_param *p)
{
	int		i;
	size_t	size;

	i = -1;
	size = ft_strlen(cmd);
	while (p->env[++i])
	{
		if (!ft_strncmp(p->env[i], cmd, size) && (p->env[i][size] == '='
			|| p->env[i][size] == '\0'))
			return (i);
	}
	return (-1);
}

char	**realloc_env(int size, t_param *p)
{
	int		i;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (size + 1));
	if (new)
	{
		while (p->env[++i] && i < size)
		{
			new[i] = ft_strdup(p->env[i]);
		}
		new[size] = 0;
		ft_free(p->env);
	}
	return (new);
}

char	*get_env(char *env, t_param *p)
{
	int 	i;
	size_t	len;

	if (!env)
		return (NULL);
	len = ft_strlen(env);
	if ((i = find_env(env, p)) != -1)
		return (ft_substr(p->env[i], (len + 1), ft_strlen(p->env[i])));
	return (NULL);
}
