/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:49:20 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/01 18:51:34 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * neg);
}

bool	is_int(char *str)
{
	int		start;
	int		len;
	long	test;

	start = 0;
	if (str[0] == '-' || str[0] == '+')
		start++;
	if (start == 1 && str[start] == '\0')
		return (false);
	while (str[start] == '0')
		start++;
	len = ft_strlen(str);
	if (len == 0 || len - start > 11)
		return (false);
	while (str[start] >= '0' && str[start] <= '9')
		start++;
	if (start != len)
		return (false);
	test = ft_atol(str);
	if (test > 2147483647 || test < -2147483648)
		return (false);
	return (true);
}

bool	is_float(char *str)
{
	int		start;
	int		len;
	char	*part;

	start = 0;
	len = 0;
	if (str[0] == '-' || str[0] == '+')
		start++;
	while (str[start + len] >= '0' && str[start + len] <= '9')
		len++;
	if (str[start + len] != '.')
		return (false);
	part = ft_substr(str, start, len);
	if (!is_int(part))
	{
		free(part);
		return (false);
	}
	free(part);
	start += len + 1;
	len = 0;
	while (str[start + len] >= '0' && str[start + len] <= '9')
		len++;
	if (str[start + len] != '\0')
		return (false);
	part = ft_substr(str, start, len);
	if (!is_int(part))
	{
		free(part);
		return (false);
	}
	free(part);
	return (true);
}
