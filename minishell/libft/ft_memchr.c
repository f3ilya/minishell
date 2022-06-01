/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:12:52 by snakita           #+#    #+#             */
/*   Updated: 2021/10/12 23:12:54 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		if (p[i] == (char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
