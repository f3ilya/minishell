#include "minishell.h"

char	**remove_env(int index, t_param *p)
{
	while (p->env[index + 1])
	{
		free(p->env[index]);
		p->env[index] = ft_strdup(p->env[index + 1]);
		index++;
	}
	return (realloc_env(index, p));
}

int	my_unset(char **cmd, t_param *p)
{
	int	i;
	int	index;

	g_status = 0;
	if (cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			index = find_env(cmd[i], p);
			if (index != -1)
			{
				if (p->env[index])
					p->env = remove_env(index, p);
			}
			else
			{
				ft_putstr_fd("minishell: unset: `", 1);
				ft_putstr_fd(cmd[i], 1);
				ft_putendl_fd("': not a valid identifier", 1);
				g_status = 1;
			}
		}
	}
	return (1);
}
