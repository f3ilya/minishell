#include "minishell.h"

void	initpipe(t_arg *argg, int argc, char **argv)
{
	int i = 0;
	while (++i < argc)
	{
		argg->arg = ft_split(argv[i], ' ');
		if (i + 1 != argc)
			argg = argg->next;
	}
	argg->next = NULL;
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
	t_param p;
	int i = 0;
	char *pwd;
	char **cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("unset");
	cmd[1] = ft_strdup("OLDPWD");

	//p.env = env;
	while (env[i])
		i++;
	p.env = malloc(sizeof (char *) * (i + 1));
	i = -1;
	while (env[++i])
		p.env[i] = env[i];
	p.pid = 0;
	p.status = 0;
	//initpipe(&arg, argc, argv);
	//printpipe(&arg);
	//pipe_list(&arg, &p);
	exec(argv + 1, 0, &p);
	exec(cmd, 0, &p);
	my_env(&p);
	return (0);
}
