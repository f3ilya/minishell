/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:15:48 by snakita           #+#    #+#             */
/*   Updated: 2021/10/12 23:15:50 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	i = 0;
	len_needle = ft_strlen((char *)needle);
	if (len_needle == 0 || !needle[0])
		return ((char *)haystack);
	while (i < len && haystack[i] && len)
	{
		if (haystack[i] == needle[0]
			&& (ft_memcmp(haystack + i, needle, len_needle)) == 0
			&& len_needle + i <= len)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
