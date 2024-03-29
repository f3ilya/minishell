/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:24:06 by                   #+#    #+#             */
/*   Updated: 2022/01/30 20:21:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <sys/types.h>

int		g_status;

typedef struct s_param {
	char	**env;
	pid_t	pid;
	int		pipe;
}	t_param;

typedef struct s_list2
{
	int				fdd0;
	int				fdd1;
	int				fd0;
	int				fd1;
	char			*pre_com;
	int				pipe;
	struct s_list2	*next;
}	t_list2;

void	signal_int(int sig);

char	**my_path(t_param *p);
int		err_out(char *str, char *str2, int status, int out);
int		ft_execve(char **cmd, char *str, t_param *p);
int		exec(char **cmd, t_param *p);
void	child_status(t_param *p);
void	pipe_list(t_list2 *arg, t_param *p, char **cmd);
void	fd_on(t_list2 *stack, int off);

int		my_echo(char **cmd);
int		my_env(t_param *p);
int		my_cd(char **cmd, t_param *p);
int		my_unset(char **cmd, t_param *p);
int		my_export(char **cmd, t_param *p);
void	my_exit(char **cmd);
void	sort_env(t_param *p);
void	ft_exit(int ex);

void	set_env(char *env, char *new_env, t_param *p);
int		find_env(char *cmd, t_param *p);
char	**realloc_env(int size, t_param *p);
char	*get_env(char *env, t_param *p);

void	ft_free(char **str);

char	*slash(char *s, int *i);
char	*gap(char *s, int *i);
char	*gap2(char *s, int *i, char **env);
char	*dollar(char *s, int *i, char **env);
void	parser(t_list2 *elem, char **env);
int		pre_parser(char *s);
int		stack_init(char *s, t_list2 **stack);
int		stack_clean(t_list2 *lst);
char	*redirects(char *s, int *i, t_list2 *elem, char **env);
char	*form_result_string(int *i, int j, char *s, char *value);
t_list2	*ft_lstnew2(char *content, int pipe);
void	ft_lstadd_back2(t_list2 **lst, t_list2 *new);
char	*ft_strjoin_free_source(char *s1, char *s2);
int		get_next_line(char **line, int fd);
int		is_space(char c);

#endif
