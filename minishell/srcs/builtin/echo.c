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

int	check_n(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		if (cmd[i][j++] == '-' && cmd[i][j] && cmd[i][j] == 'n'
			&& !cmd[i][j + 1])
			return (1);
	}
	return (0);
}

int	my_echo(char **cmd)
{
	int	n;
	int	i;

	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	i = check_n(cmd);
	n = i++;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "$?", 3))
			ft_putnbr_fd(g_status, 1);
		else
			ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	g_status = 0;
	return (1);
}
