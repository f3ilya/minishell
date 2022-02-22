#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	g_env = env;
	return (exec(argv + 1, 0));
}
