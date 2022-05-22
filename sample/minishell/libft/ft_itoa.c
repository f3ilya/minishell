/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:40:09 by snakita           #+#    #+#             */
/*   Updated: 2021/10/16 18:40:11 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_uhh(char *str, int n, size_t j)
{
	int	i;

	i = j - 1;
	while (n > 9)
	{
		str[i--] = 48 + (n % 10);
		n = n / 10;
	}
	str[i] = n % 10 + 48;
	str[j] = '\0';
	return (str);
}

static size_t	ft_its(int n)
{
	size_t	j;

	j = 0;
	if (n <= 0)
		j = 1;
	while (n)
	{
		n = n / 10;
		j++;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	k;

	i = 0;
	k = ft_its(n);
	str = (char *)malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		str[i] = '-';
		str[i + 1] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		str[i] = '-';
		n = -n;
	}
	return (ft_uhh(str, n, k));
}
