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

int my_unset(char **cmd, t_param *p)
{
	int i;
	int index;

	p->status = 0;
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
				p->status = 1;
			}
		}
	}
	return (1);
}
