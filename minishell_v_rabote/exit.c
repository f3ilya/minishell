#include "minishell.h"

void	ft_exit(t_param *p)
{
	exit(p->status);
}

void	exit_error(char *cmd, t_param *p)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": numeric argument required", 2);
	p->status = 2;
	ft_exit(p);
}

int	ft_atoi_exit(const char *str, t_param *p)
{
	int			i;
	int			k;
	long int	n;

	i = 0;
	k = 1;
	n = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		k = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + k * (str[i++] - 48);
		if ((k == 1 && n < 0 && i > 18) || (k == -1 && n > 0 && i > 19))
			exit_error(str, p);
	}
	return (n);
}

void	exit_check(char *cmd, t_param *p)
{
	int i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '\n' || cmd[i] == '\r'
			|| cmd[i] == '\v' || cmd[i] == '\t' || cmd[i] == '\f'
			|| cmd[i] < 48 || cmd[i] > 57)
			exit_error(cmd, p);
		i++;
	}
}

void	my_exit(char **cmd, t_param *p)
{
	p->status = 0;
	if (!cmd[1])
		ft_exit(p);
	exit_check(cmd[1], p);
	if (cmd && cmd[1] && cmd[2])
		err_out(cmd[0], ": too many arguments", 1, 1, p);
	else
		p->status = ft_atoi_exit(cmd[1], p) % 256;
	ft_exit(p);
}
