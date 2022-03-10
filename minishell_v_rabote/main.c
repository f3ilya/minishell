#include "minishell.h"

void	initpipe(t_arg *arg, int argc, char **argv)
{
	int i = 0;
	while (++i < argc)
	{
		arg->arg = ft_split(argv[i], ' ');
		if (i + 1 != argc)
			arg = arg->next;
	}
}

void	printpipe(t_arg *arg)
{
	int i = 0;
	while (i < 3)
	{
		printf("%s\n", arg->arg[0]);
		i++;
		if (i < 3)
			arg = arg->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_arg arg;

	g_env = env;
	g_pid = 0;
	g_status = 0;
	initpipe(&arg, argc, argv);
	//printpipe(&arg);
	pipe_list(&arg);
	return (0);
}
