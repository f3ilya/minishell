#include "minishell.h"

t_arg	*ft_lstnw(char *str)
{
	t_arg	*elem;

	elem = malloc(sizeof(t_arg));
	if (elem)
	{
		elem->arg = ft_split(str, ' ');
		elem->prev = NULL;
		elem->next = NULL;
	}
	return (elem);
}

void	ft_lstadd_backk(t_arg **lst, t_arg *new)
{
	t_arg	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
		new->prev = *lst;
	}
	else
		*lst = new;
}

t_arg	*initpipe(char **argv)
{
//	int i = 0;
//	while (++i < argc)
//	{
//		argg->arg = ft_split(argv[i], ' ');
//		if (i + 1 != argc)
//			argg = argg->next;
//	}
//	argg->next = NULL;
	t_arg *res;
	int		i;

	i = 0;
	res = 0;
	while (argv[++i])
		ft_lstadd_backk(&res, ft_lstnw(argv[i]));
	return res;
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
	t_arg *arg;
	t_param p;
	int i = 0;
	char *pwd;
	char **cmd;

//	cmd = malloc(sizeof(char *) * 2);
//	cmd[0] = ft_strdup("unset");
//	cmd[1] = ft_strdup("OLDPWD");
	cmd = ft_split("unset PWD HOME", ' ');

	while (env[i])
		i++;
	p.env = malloc(sizeof (char *) * (i + 1));
	i = -1;
	while (env[++i])
		p.env[i] = ft_strdup(env[i]);
	p.pid = 0;
	p.status = 0;
	//arg = initpipe(argv);
	//printpipe(&arg);
	//pipe_list(arg, &p);
	exec(argv + 1, 0, &p);
	exec(cmd, 0, &p);
	my_env(&p);
	printf("%d\n", p.status);
//	i = -1;
//	while (cmd[++i])
//		printf("%s\n", cmd[i]);
	return (0);
}
