#include "minishell.h"

void	set_env(char *env, char *new_env, t_param *p)
{
	int i;

	i = -1;
	while (p->env[++i])
	{
		if (!ft_strncmp(p->env[i], env, ft_strlen(env)))
		{
			p->env[i] = ft_strjoin(env, new_env);
			return ;
		}
	}
	p->env[i] = ft_strjoin(env, new_env);
}

int find_env(char *cmd, t_param *p)
{
	int 	i;
	size_t	size;

	i = -1;
	size = ft_strlen(cmd);
	while (p->env[++i])
	{
		if (!ft_strncmp(p->env[i], cmd, size) && cmd[size + 1] == '=')
			return (i);
	}
	return (-1);
}

char	**realloc_env(int size, t_param *p)
{
	int 	i;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (size + 1));
	if (new)
	{
		while (p->env[++i] && i < size)
			new[i] = ft_strdup(p->env[i]);
		new[size] = 0;
		ft_free(p->env);
	}
	return (new);
}
