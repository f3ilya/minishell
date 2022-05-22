/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:09:59 by snakita           #+#    #+#             */
/*   Updated: 2021/10/12 23:10:10 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			k;
	long int	n;

	i = 0;
	k = 1;
	n = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		k = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + k * (str[i++] - 48);
		if (k == 1 && n < 0 && i > 18)
			return (-1);
		else if (k == -1 && n > 0 && i > 19)
			return (0);
	}
	return (n);
}
