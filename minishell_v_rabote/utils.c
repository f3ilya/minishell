#include "minishell.h"

void	ft_free(char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		//ft_putendl_fd(str[i], 1);
		if (str[i])
			free(str[i]);
	}
}
