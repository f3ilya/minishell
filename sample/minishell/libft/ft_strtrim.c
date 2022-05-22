/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:39:42 by snakita           #+#    #+#             */
/*   Updated: 2021/10/16 18:39:43 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	len = ft_strlen((char *)s1 + i);
	while (ft_strchr(set, s1[len + i - 1]) && s1[i])
		len--;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
