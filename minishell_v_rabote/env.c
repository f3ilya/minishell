#include "minishell.h"

int my_env(t_param *p)
{
	int i;

	i = -1;
	p->status = 0;
	while (p->env[++i])
		ft_putendl_fd(p->env[i], 1);
	return (1);
}
