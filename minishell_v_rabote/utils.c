#include "minishell.h"

void	ft_free(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
}
