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
# include <limits.h>
# include <errno.h>
#include "libft.h"
//# include "readline/history.h"
//# include "readline/readline.h"

int		g_status;


typedef struct s_param {
	char	**env;
	int		status;
	pid_t 	pid;
} t_param;

typedef struct s_arg {
	char 			**arg;
	struct s_arg 	*next;
	struct s_arg 	*prev;
} t_arg;

void    signal_int(int sig);

char	**my_path();
int		err_out(char *str, char *str2, int status, int out);
int		ft_execve(char **cmd, char *str, int pipe, t_param *p);
int		exec(char **cmd, int pipe, t_param *p);
void	child_status(t_param *p);
void	pipe_list(t_arg *arg, t_param *p);

int		my_echo(char **cmd, t_param *p);
int		my_env(t_param *p);
int		my_cd(char **cmd, t_param *p);
int 	my_unset(char **cmd, t_param *p);
int		my_export(char **cmd, t_param *p);
void	my_exit(char **cmd);
void	sort_env(t_param *p);
void	ft_exit(void);

void	set_env(char *env, char *new_env, t_param *p);
int		find_env(char *cmd, t_param *p);
char	**realloc_env(int size, t_param *p);

void	ft_free(char **str);

#endif
