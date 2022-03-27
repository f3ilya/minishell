#include "minishell.h"

int check_n(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		if (cmd[i][j++] == '-' && cmd[i][j] && cmd[i][j] == 'n' && !cmd[i][j + 1])
			return (1);
	}
	return (0);
}

int my_echo(char **cmd, t_param *p)
{
	int n;
	int i;

	p->status = 0;
	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	i = check_n(cmd);
	n = i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (1);
}
