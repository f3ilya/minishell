#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <string.h>
#include <signal.h>
#include "libft.h"

char	**g_env;
int		g_status;
pid_t 	g_pid;

typedef struct s_arg {
	char 			**arg;
	int				fd[2];
	struct s_arg 	*next;
	struct s_arg 	*prev;
} t_arg;

char	**my_path();
int		err_out(char *str, char *str2, int status, int out);
int		ft_execve(char **cmd, char *str, int pipe);
int		exec(char **cmd, int pipe);
void	child_status(void);
void	pipe_list(t_arg *arg);

#endif
