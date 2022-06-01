/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:39:07 by snakita           #+#    #+#             */
/*   Updated: 2021/10/16 18:39:12 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = len;
	if (len > ft_strlen(s))
		i = ft_strlen(s);
	str = (char *)malloc(i + 1);
	if (str)
	{
		i = 0;
		while (start-- > 0 && *s)
			s++;
		while (*s && i < len)
		{
			str[i] = *s++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
