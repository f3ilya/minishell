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
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"

int		g_status;

typedef struct s_param {
	char	**env;
	pid_t 	pid;
} t_param;

typedef struct s_arg {
	char 			**arg;
	struct s_arg 	*next;
	struct s_arg 	*prev;
} t_arg;

typedef struct s_list2
{
	int				fd0;
	int				fd1;
	char			**com;
	char			*pre_com;
	int				pipe;
	struct s_list2	*next;
}	t_list2;

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

char	*slash(char *s, int *i);
char	*gap(char *s, int *i);
char	*gap2(char *s, int *i, char **env);
char	*dollar(char *s, int *i, char **env);
void	parser(t_list2 *elem, char **env);
int		pre_parser(char *s);
int		stack_init(char *s, t_list2 **stack);
char	*redirects(char *s, int *i, t_list2 *elem, char **env);
char	*form_result_string(int *i, int j, char *s, char *value);
t_list2	*ft_lstnew2(char *content, int pipe);
void	ft_lstprint(t_list2 *lst);
void	ft_lstadd_back2(t_list2 **lst, t_list2 *new);
int	ft_lstsize2(t_list2 *lst);
t_list2	*ft_lstlast2(t_list2 *lst);
char	*ft_strjoin_free_source(char *s1, char *s2);

#endif
