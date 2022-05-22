#include "minishell.h"

static void	print_export(char **env)
{
	int	i;
	int	j;
	int	t;

	i = -1;
	while (env[++i])
	{
		t = 1;
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=' && t)
			{
				ft_putchar_fd('"', 1);
				t--;
			}
		}
		if (!t)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
	}
}

static char	**envdup(t_param *p)
{
	int		i;
	char	**new;

	i = 0;
	while (p->env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (new)
	{
		i = -1;
		while (p->env[++i])
			new[i] = ft_strdup(p->env[i]);
		new[i] = 0;
	}
	return (new);
}

void	sort_env(t_param *p)
{
	char	**env;
	char	*tmp;
	int		i;
	int		j;

	env = envdup(p);
	i = -1;
	while (env[++i])
	{
		j = i;
		while (env[++j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
	print_export(env);
	ft_free(env);
}
