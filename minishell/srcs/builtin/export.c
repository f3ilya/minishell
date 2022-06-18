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

static int	check_export(char *name)
{
	int	i;
	int	t;

	i = -1;
	t = 0;
	if (!name || !name[0] || name[0] == '=')
		return (0);
	while (name[++i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
			t = 1;
		else if (!ft_isdigit(name[i]) || (ft_isdigit(name[i]) && !t))
			return (0);
	}
	return (1);
}

static void	add_export(char *cmd, t_param *p)
{
	int		i;
	char	*end;
	char	*new;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	end = ft_strchr(cmd, '=');
	if (end)
	{
		new = ft_substr(cmd, 0, i);
		set_env(new, end, p);
		free(new);
	}
	else
		set_env(cmd, "", p);
}

int	my_export(char **cmd, t_param *p)
{
	int	i;

	g_status = 0;
	i = 0;
	if (cmd[1])
	{
		while (cmd[++i])
		{
			if (check_export(cmd[i]))
				add_export(cmd[i], p);
			else
			{
				ft_putstr_fd("minishell: export: `", 1);
				ft_putstr_fd(cmd[i], 1);
				ft_putendl_fd("': not a valid identifier", 1);
				g_status = 1;
			}
		}
	}
	else
		sort_env(p);
	return (1);
}
