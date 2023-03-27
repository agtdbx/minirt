/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:49:20 by aderouba          #+#    #+#             */
/*   Updated: 2023/03/27 16:00:38 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	is_int(char const *str)
{
	int		start;
	int		len;
	long	test;

	if (!str)
		return (false);
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

bool	is_float(char const *str)
{
	int		start;
	int		len;
	char	*part;

	if (!str)
		return (false);
	start = 0;
	len = 0;
	if (str[0] == '-' || str[0] == '+')
		start++;
	while (str[start + len] >= '0' && str[start + len] <= '9')
		len++;
	if (str[start + len] != '.' && str[start + len] != '\0')
		return (false);
	part = ft_substr(str, start, len);
	if (!is_int(part))
	{
		free(part);
		return (false);
	}
	free(part);
	if (str[start + len] == '\0')
		return (true);
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
