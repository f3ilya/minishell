/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:02:56 by                   #+#    #+#             */
/*   Updated: 2021/12/07 13:02:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

t_list2	*ft_lstnew2(char *content, int pipe)
{
	t_list2	*elem;

	elem = malloc(sizeof(t_list2));
	if (!elem)
		return (NULL);
	elem->pre_com = content;
	elem->com = ft_split(content, ' ');
	elem->fdd0 = 1000;
	elem->fdd1 = 1001;
	elem->fd0 = 0;
	elem->fd1 = 1;
	elem->pipe = pipe;
	elem->next = NULL;
	return (elem);
}

void	ft_lstprint(t_list2 *lst)
{
	while (lst)
	{
		printf("!%s! - %20d - %d - %d\n",
			lst->pre_com, lst->fd0, lst->fd1, lst->pipe);
		lst = lst->next;
	}
}

void	ft_lstadd_back2(t_list2 **lst, t_list2 *new)
{
	t_list2	*el;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	el = *lst;
	while (el->next)
		el = el->next;
	el->next = new;
}

int	ft_lstsize2(t_list2 *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list2	*ft_lstlast2(t_list2 *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
