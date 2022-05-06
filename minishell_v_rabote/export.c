#include "minishell.h"

static int check_export(char *name)
{
	int	i;
	int t;

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
	int 	i;
	char	*end;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	end = ft_strchr(cmd, '=');
	if (end)
		set_env(ft_substr(cmd, 0, i + 1), end + 1, p);
	else
		set_env(cmd, end, p);

}

int	my_export(char **cmd, t_param *p)
{
	int i;

	p->status = 0;
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
				p->status = 1;
			}
		}
	}
	else
		sort_env(p);
	return (1);
}