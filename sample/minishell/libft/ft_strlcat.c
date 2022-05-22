/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:18:58 by snakita           #+#    #+#             */
/*   Updated: 2021/10/12 23:19:00 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (j < dstsize)
	{
		while (j + i < dstsize - 1 && src[i])
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
	}
	i = ft_strlen((char *)src);
	if (j >= dstsize)
		j = dstsize;
	return (i + j);
}
